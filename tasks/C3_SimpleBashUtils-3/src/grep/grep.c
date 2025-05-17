#include <ctype.h>
#include <locale.h>
#include <malloc.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TYPE char
#define NAME char
#include "../common/vector/vector_decl.h"
#include "../common/vector/vector_defn.h"
#undef TYPE
#undef NAME

#define TYPE regex_t
#define NAME regex
#include "../common/vector/vector_decl.h"
#include "../common/vector/vector_defn.h"
#undef TYPE
#undef NAME

#define RED "\e[1;31m"
#define PUR "\e[0;35m"
#define BLU "\e[0;34m"
#define GRN "\e[0;32m"
#define DFT "\e[0m"

#include "../common/command_line_parser/command_line_parser.h"

struct grep_state {
  char_vec *patterns;
  int cflags, file_count;
  bool multiple_patterns, inverse_match, count_matching_lines,
      ignore_matching_line, only_matching_files, print_line_num,
      ignore_filename, suppress_errors, only_match;
};

int i_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  state->cflags |= REG_ICASE;

  return 0;
}

int v_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  state->inverse_match = true;

  return 0;
}

int c_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  if (!state->only_matching_files) {
    state->count_matching_lines = true;
    state->ignore_matching_line = true;
  }

  return 0;
}

int l_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  state->only_matching_files = true;

  state->count_matching_lines = false;
  state->ignore_matching_line = true;

  return 0;
}

int n_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  state->print_line_num = true;

  return 0;
}

int h_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  state->ignore_filename = true;

  return 0;
}

int s_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  state->suppress_errors = true;

  return 0;
}

int o_flag(struct grep_state *state, void *args) {
  (void)args;
  if (!state) return -1;

  state->only_match = true;

  return 0;
}

int e_flag(struct grep_state *state, char **args) {
  if (!(state && state->patterns && args && *args)) return -1;
  int exit_stat = 0;

  exit_stat |= char_vec_add_all(state->patterns,
                                (char_arr){.dat = *args, .len = strlen(*args)});
  exit_stat |= char_vec_add(state->patterns, '\n');
  state->multiple_patterns = true;

  return exit_stat;
}

int f_flag(struct grep_state *state, char **args) {
  if (!(state && state->patterns && args && *args)) return -1;
  int exit_stat = 0;

  char *filename = *args;
  FILE *file = fopen(filename, "rt");

  if (file) {
    char buf[BUFSIZ] = {0};
    int len_read = 0;
    while ((len_read = fread(buf, sizeof(char), BUFSIZ, file))) {
      exit_stat |= char_vec_add_all(state->patterns,
                                    (char_arr){.dat = buf, .len = len_read});
    }

    if (state->patterns->dat[state->patterns->len - 1] != '\n')
      exit_stat |= char_vec_add(state->patterns, '\n');

    fclose(file);
  } else
    exit_stat = -1;
  state->multiple_patterns = true;

  return exit_stat;
}

static inline int compile_regexes(char *patterns, regex_vec *regexes,
                                  int cflags, bool *only_blanks) {
  if (!(patterns && regexes && regexes->dat)) return -1;
  int exit_stat = 0;

  char *pattern = patterns;
  while (!exit_stat && pattern) {
    char *next_delim = strchr(pattern, '\n');
    if (next_delim) *next_delim++ = 0;
    regex_t regex;
    if (pattern[0]) *only_blanks = false;
    if (regcomp(&regex, pattern, cflags) == 0)
      exit_stat |= regex_vec_add(regexes, regex);
    else
      exit_stat = -1;
    pattern = next_delim;
  }

  return exit_stat;
}

static inline int append_colored_string(char_vec *str_to_modify, char *color,
                                        char_arr str) {
  if (!(str_to_modify && str_to_modify->dat && color && str.dat)) return -1;
  int exit_stat = 0;

  if (isatty(STDOUT_FILENO))
    exit_stat |= char_vec_add_all(
        str_to_modify, (char_arr){.dat = color, .len = strlen(color)});

  exit_stat |= char_vec_add_all(str_to_modify, str);

  if (isatty(STDOUT_FILENO))
    exit_stat |= char_vec_add_all(str_to_modify,
                                  (char_arr){.dat = DFT, .len = strlen(DFT)});

  return exit_stat;
}

static inline int append_match_string(struct grep_state state,
                                      char_vec *str_to_modify,
                                      regmatch_t *pmatch, char *substr) {
  if (!(str_to_modify && str_to_modify->dat && pmatch && substr)) return -1;
  int exit_stat = 0;

  int bytes_read = pmatch->rm_eo - pmatch->rm_so;
  if (!state.only_match)
    exit_stat |= char_vec_add_all(str_to_modify,
                                  (char_arr){.dat = substr, pmatch->rm_so});
  if (bytes_read)
    exit_stat |= append_colored_string(
        str_to_modify, RED,
        (char_arr){.dat = substr + pmatch->rm_so, .len = bytes_read});

  return exit_stat;
}

static inline int append_filename(char_vec *str_to_modify, char *filename) {
  return append_colored_string(
      str_to_modify, PUR, (char_arr){.dat = filename, .len = strlen(filename)});
}

static inline int append_blue_colon(char_vec *str_to_modify) {
  return append_colored_string(str_to_modify, BLU,
                               (char_arr){.dat = ":", .len = 1});
}

static inline int append_line_num(struct grep_state state,
                                  char_vec *str_to_modify, int line_num) {
  if (!(str_to_modify && str_to_modify->dat)) return -1;
  if (!state.print_line_num) return 0;
  int exit_stat = 0;

  char str_num[256] = {0};
  sprintf(str_num, "%d", line_num);
  exit_stat |= append_colored_string(
      str_to_modify, GRN, (char_arr){.dat = str_num, .len = strlen(str_num)});
  exit_stat |= append_blue_colon(str_to_modify);

  return exit_stat;
}

static inline int append_full_filename(struct grep_state state,
                                       char_vec *str_to_modify,
                                       char *filename) {
  int exit_stat = 0;
  if (state.file_count > 1 && !state.ignore_filename) {
    exit_stat |= append_filename(str_to_modify, filename);
    exit_stat |= append_blue_colon(str_to_modify);
  }
  return exit_stat;
}

static inline int process_line(struct grep_state state, regex_vec *regexes,
                               char_vec *line, FILE *file, char *filename,
                               int line_num, bool *contains_match) {
  if (!(regexes && regexes->dat && line && line->dat && file && filename &&
        contains_match))
    return -1;
  int exit_stat = 0;

  char_vec str_to_print = {0};
  if (!state.ignore_matching_line) {
    exit_stat |= char_vec_alloc(2, &str_to_print);

    if (!exit_stat && !state.only_match) {
      exit_stat |= append_full_filename(state, &str_to_print, filename);
      exit_stat |= append_line_num(state, &str_to_print, line_num);
    }
  }

  bool any_line_match = false, any_rest_match;
  char *rest = line->dat;
  do {
    any_rest_match = false;
    regmatch_t first_match;
    for (size_t iregex = 0; iregex < regexes->len &&
                            !(state.ignore_matching_line && any_line_match);
         iregex++) {
      regex_t regex = regexes->dat[iregex];
      regmatch_t pmatch;
      if (regexec(&regex, rest, 1, &pmatch, 0) == 0 &&
          (!any_rest_match || pmatch.rm_so < first_match.rm_so ||
           (pmatch.rm_so == first_match.rm_so &&
            pmatch.rm_eo > first_match.rm_eo))) {
        any_line_match = true;
        any_rest_match = true;
        first_match = pmatch;
      }
    }
    if (any_rest_match) {
      int bytes_read = first_match.rm_eo - first_match.rm_so;
      if (bytes_read == 0)
        first_match.rm_eo = first_match.rm_so = first_match.rm_so + 1;
      if (!state.inverse_match && !state.ignore_matching_line) {
        if (state.only_match && bytes_read) {
          exit_stat |= append_full_filename(state, &str_to_print, filename);
          exit_stat |= append_line_num(state, &str_to_print, line_num);
        }
        exit_stat |=
            append_match_string(state, &str_to_print, &first_match, rest);
        if (state.only_match && bytes_read)
          exit_stat |= char_vec_add(&str_to_print, '\n');
      }
      rest += first_match.rm_eo;
    }
  } while (any_rest_match && *rest);
  if (any_line_match ^ state.inverse_match) {
    *contains_match = true;
    if (!state.ignore_matching_line) {
      if (!state.only_match)
        exit_stat |= char_vec_add_all(
            &str_to_print,
            (char_arr){.dat = rest, .len = line->dat + line->len - rest});
      if (str_to_print.len) {
        if (!memchr(str_to_print.dat, 0, str_to_print.len))
          exit_stat |= char_vec_add(&str_to_print, 0);
        if (!strchr(str_to_print.dat, '\n'))
          exit_stat |=
              char_vec_add_i(&str_to_print, '\n', str_to_print.len - 1);
        printf("%s", str_to_print.dat);
      }
    }
  }

  if (str_to_print.dat) char_vec_free(&str_to_print);
  char_vec_clear(line);

  return exit_stat;
}

static inline int process_file(struct grep_state state, regex_vec *regexes,
                               char_vec *line, FILE *file, char *filename) {
  if (!(regexes && regexes->dat && line && line->dat && file && filename))
    return -1;
  int exit_stat = 0;

  static char buf[BUFSIZ] = {0};
  int matching_line_count = 0;
  int line_count = 0;
  while (!exit_stat && fgets(buf, BUFSIZ, file) != NULL) {
    int bytes_read = strlen(buf);
    exit_stat |=
        char_vec_add_all(line, (char_arr){.dat = buf, .len = bytes_read + 1});
    if (buf[bytes_read - 1] == '\n' || feof(file)) {
      line_count++;
      bool line_contains_match = false;
      if (buf[bytes_read - 1] == '\n') char_vec_rm(line, line->len - 2);
      exit_stat |= process_line(state, regexes, line, file, filename,
                                line_count, &line_contains_match);
      if (line_contains_match) matching_line_count++;
    }
  }
  if (!exit_stat && (state.count_matching_lines || state.only_matching_files)) {
    char_vec str_to_print;
    int filename_len = strlen(filename);
    if (char_vec_alloc(filename_len + 16, &str_to_print) == 0) {
      if (state.only_matching_files) {
        if (matching_line_count > 0)
          exit_stat |= append_filename(&str_to_print, filename);
      } else if (state.file_count > 1 && !state.ignore_filename)
        exit_stat |= append_full_filename(state, &str_to_print, filename);

      if (state.count_matching_lines) {
        char buf[256];
        sprintf(buf, "%d", matching_line_count);
        char_vec_add_all(&str_to_print,
                         (char_arr){.dat = buf, .len = strlen(buf)});
      }

      if (str_to_print.len) exit_stat |= char_vec_add(&str_to_print, '\n');
      exit_stat |= char_vec_add(&str_to_print, 0);
      printf("%s", str_to_print.dat);

      char_vec_free(&str_to_print);
    } else
      exit_stat = -1;
  }

  return exit_stat;
}

static inline void free_regexes(regex_vec *regexes) {
  if (regexes->dat) {
    for (size_t iregex = 0; iregex < regexes->len; iregex++) {
      regfree(regexes->dat + iregex);
    }
    regex_vec_free(regexes);
  }
}

int main(int argc, char **argv) {
  int exit_stat = 0;

  setlocale(LC_ALL, "");

  char_vec patterns = {0};
  exit_stat |= char_vec_alloc(2, &patterns);
  struct grep_state state = {.patterns = &patterns, 0};

  str_arr parameters;
  exit_stat |= parse_line(
      (str_arr){.dat = argv, .len = argc}, (void *)&state,
      (op_arr){
          .dat = (option[]){(option){.apply = (int (*)(void *, char **))e_flag,
                                     .label = 'e',
                                     .arity = 1},
                            (option){.apply = (int (*)(void *, char **))i_flag,
                                     .label = 'i',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))v_flag,
                                     .label = 'v',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))c_flag,
                                     .label = 'c',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))l_flag,
                                     .label = 'l',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))n_flag,
                                     .label = 'n',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))h_flag,
                                     .label = 'h',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))s_flag,
                                     .label = 's',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))o_flag,
                                     .label = 'o',
                                     .arity = 0},
                            (option){.apply = (int (*)(void *, char **))f_flag,
                                     .label = 'f',
                                     .arity = 1}},
          .len = 10},
      &parameters);
  if (patterns.dat) {
    if (!state.multiple_patterns) {
      exit_stat |= char_vec_add_all(
          &patterns, (char_arr){.dat = parameters.dat[1],
                                .len = strlen(parameters.dat[1])});
    } else
      exit_stat |= char_vec_rm(&patterns, patterns.len - 1);
    exit_stat |= char_vec_add(&patterns, 0);
  }

  bool only_blanks = true;
  regex_vec regexes = {0};
  exit_stat |= regex_vec_alloc(1, &regexes);
  exit_stat |=
      compile_regexes(patterns.dat, &regexes, state.cflags, &only_blanks);

  // Strange condition but grep does this thing 🤷‍♂
  if (only_blanks && state.inverse_match && state.count_matching_lines)
    exit_stat = 1;

  if (patterns.dat) char_vec_free(&patterns);

  char_vec line;
  exit_stat |= char_vec_alloc(BUFSIZ, &line);
  state.file_count = parameters.len - (state.multiple_patterns ? 1 : 2);
  // printf("%s\n", parameters.dat[1]);
  for (int ifile = (state.multiple_patterns ? 1 : 2);
       !exit_stat && ifile < parameters.len; ifile++) {
    char *filename = parameters.dat[ifile];
    FILE *file = fopen(filename, "rt");

    if (file) {
      exit_stat |= process_file(state, &regexes, &line, file, filename);
      fclose(file);
    } else {
      exit_stat = -1;
      if (!state.suppress_errors) {
        fprintf(stderr, "grep: %s: No such file or directory\n", filename);
      }
    }
  }

  if (line.dat) char_vec_free(&line);
  free_regexes(&regexes);
  if (parameters.dat) free(parameters.dat);

  return exit_stat;
}
