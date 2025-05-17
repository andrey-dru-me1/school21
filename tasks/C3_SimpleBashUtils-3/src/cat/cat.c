#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

#include "../common/command_line_parser/command_line_parser.h"

struct flags {
  bool number_lines, number_blank_lines, squeeze_blank, print_newline,
      print_tab, show_nonprinting;
};

int n_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  if (!flags->number_lines) {
    flags->number_lines = true;
    flags->number_blank_lines = true;
  }

  return 0;
}

int b_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  flags->number_lines = true;
  flags->number_blank_lines = false;

  return 0;
}

int s_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  flags->squeeze_blank = true;
  return 0;
}

int E_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  flags->print_newline = true;
  return 0;
}

int e_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  flags->print_newline = true;
  flags->show_nonprinting = true;
  return 0;
}

int v_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  flags->show_nonprinting = true;
  return 0;
}

int T_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  flags->print_tab = true;
  return 0;
}

int t_flag(struct flags *flags, void *args) {
  (void)args;
  if (!flags) return -1;

  flags->print_tab = true;
  flags->show_nonprinting = true;
  return 0;
}

static void print_non_printing(char c) {
  if (c < -96) {
    printf("M-^%c", c + 192);
  } else if (c < -1) {
    printf("M-%c", c + 128);
  } else if (c == -1) {
    printf("M-^?");
  } else if (c < 32) {
    printf("^%c", c + 64);
  } else {
    printf("^?");
  }
}

int main(int argc, char **argv) {
  int exit_status = 0;

  struct flags flags = {false};
  str_arr file_names;
  exit_status = parse_line(
      (str_arr){.dat = (char **)argv, .len = argc}, (void *)&flags,
      (op_arr){
          .dat = (option[]){(option){.apply = (int (*)(void *, char **))n_flag,
                                     .label = 'n',
                                     .long_label = "number"},
                            (option){.apply = (int (*)(void *, char **))s_flag,
                                     .label = 's',
                                     .long_label = "squeeze-blank"},
                            (option){.apply = (int (*)(void *, char **))b_flag,
                                     .label = 'b',
                                     .long_label = "number-nonblank"},
                            (option){.apply = (int (*)(void *, char **))E_flag,
                                     .label = 'E'},
                            (option){.apply = (int (*)(void *, char **))e_flag,
                                     .label = 'e'},
                            (option){.apply = (int (*)(void *, char **))v_flag,
                                     .label = 'v'},
                            (option){.apply = (int (*)(void *, char **))t_flag,
                                     .label = 't'},
                            (option){.apply = (int (*)(void *, char **))T_flag,
                                     .label = 'T'}},
          .len = 8},
      &file_names);

  int line_num = 1;
  bool newline = true;
  int blank_line_count = 0;
  for (int ifile = 1; !exit_status && ifile < file_names.len; ifile++) {
    char *filename = ((char **)file_names.dat)[ifile];
    FILE *file = fopen(filename, "r");
    if (file) {
      char buf[BUFSIZ];
      int bytes;
      while ((bytes = fread(buf, sizeof(char), BUFSIZ, file))) {
        buf[bytes] = 0;
        for (int i = 0; i < bytes; i++) {
          char c = buf[i];

          blank_line_count =
              (c == '\n') ? blank_line_count + ((newline) ? 1 : 0) : 0;

          if (!(flags.squeeze_blank && blank_line_count > 1)) {
            if ((flags.number_lines && !blank_line_count && newline) ||
                (flags.number_blank_lines && blank_line_count))
              printf("%6d\t", line_num++);
            if (flags.show_nonprinting &&
                !(isprint(c) || c == '\n' || c == '\t')) {
              print_non_printing(c);
            } else {
              if (flags.print_newline && c == '\n') printf("$");
              if (flags.print_tab && c == '\t')
                printf("^I");
              else
                putchar(c);
            }
          }
          newline = (c == '\n');
        }
      }
      fclose(file);
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n", filename);
      exit_status = 1;
    }
  }

  if (file_names.dat) free(file_names.dat);

  return exit_status;
}
