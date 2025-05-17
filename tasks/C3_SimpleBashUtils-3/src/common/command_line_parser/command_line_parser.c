#include "command_line_parser.h"

#include <malloc.h>
#include <stdio.h>

#define TYPE char *
#define NAME str
#include "../vector/vector_defn.h"
#undef TYPE
#undef NAME

static int get_option_by_label(op_arr available_options, char label,
                               option *res_op) {
  int exit_status = -1;
  for (int i = 0; exit_status && i < available_options.len; i++) {
    option op = available_options.dat[i];
    if (label == op.label) {
      *res_op = op;
      exit_status = 0;
    }
  }
  return exit_status;
}

static int get_option_by_long_label(op_arr available_options, char *long_label,
                                    option *res_op) {
  int exit_status = -1;
  for (int i = 0; exit_status && i < available_options.len; i++) {
    option op = available_options.dat[i];
    if (op.long_label && strcmp(long_label, op.long_label) == 0) {
      *res_op = op;
      exit_status = 0;
    }
  }
  return exit_status;
}

static inline int handle_options(op_arr available_options, void *obj,
                                 char *labels, option *op,
                                 char **inline_param) {
  int exit_status = 0;
  int op_res = 0, j = 0;
  while (!exit_status && labels[j] &&
         (op_res = get_option_by_label(available_options, labels[j], op)) ==
             0 &&
         op->arity == 0) {
    // It is guaranteed that op has 0 arity in here so anything can be
    // passed as a pointer to args
    if (op->apply(obj, NULL)) {
      exit_status = -1;
      fprintf(stderr, "Cannot apply instructions for option '%c'.\n",
              op->label);
    }
    j++;
  }

  if (!exit_status && op_res) {
    exit_status = -1;
    fprintf(stderr, "Cannot find an option '%c'.\n", labels[j]);
  }

  if (!exit_status && labels[j] && labels[j + 1]) {
    if (op->arity == 1) {
      if (labels[j + 1] == '=') {
        *inline_param = labels + j + 2;
      } else {
        *inline_param = labels + j + 1;
      }
    } else {
      exit_status = -1;
      fprintf(
          stderr,
          "An option in a row of options should have either 0 or 1 arity but "
          "option '%c' has '%d' arity.\n",
          labels[j], op->arity);
    }
  }
  return exit_status;
}

static inline int handle_long_option(op_arr available_options, char *long_label,
                                     option *op, char **inline_param) {
  int exit_status = 0;

  char *label = calloc(strlen(long_label) + 1, sizeof(char));
  if (!label) {
    exit_status = -1;
    fprintf(stderr, "Allocation error ocurred");
  } else {
    memcpy(label, long_label, strlen(long_label));
    char *eq_ptr = strchr(label, '=');
    if (eq_ptr) {
      *eq_ptr = 0;
      *inline_param = long_label + strlen(label) + 1;
    }
  }

  if (!exit_status && get_option_by_long_label(available_options, label, op)) {
    exit_status = -1;
    fprintf(stderr, "Cannot find a long option '%s'.\n", label);
  }

  if (label) free(label);
  return exit_status;
}

int parse_line(const str_arr line_to_parse, void *obj, op_arr available_options,
               str_arr *line_parameters) {
  int exit_status = 0;

  str_vec params;
  if (str_vec_alloc(0, &params) != 0) {
    exit_status = -1;
    fprintf(stderr, "Allocation error");
  }

  char **args = line_to_parse.dat;

  for (int i = 0; !exit_status && i < line_to_parse.len; i++) {
    // If an option
    if (args[i][0] == '-' && args[i][1]) {
      option op = {0};
      char *inline_param = NULL;
      if (args[i][1] == '-') {
        exit_status = handle_long_option(available_options, args[i] + 2, &op,
                                         &inline_param);
      } else {
        exit_status = handle_options(available_options, obj, args[i] + 1, &op,
                                     &inline_param);
      }

      if (!exit_status && (!((inline_param && !op.apply(obj, &inline_param)) ||
                             (line_to_parse.len - i - 1 >= op.arity &&
                              !op.apply(obj, args + i + 1))))) {
        exit_status = -1;
        fprintf(stderr, "Illegal option's argument(s).\n");
      }

      if (!exit_status && !inline_param) i += op.arity;
    } else {
      str_vec_add(&params, args[i]);
    }
  }
  if (!exit_status)
    *line_parameters = (str_arr){.dat = params.dat, .len = params.len};
  else if (params.dat) {
    free(params.dat);
  }
  return exit_status;
}
