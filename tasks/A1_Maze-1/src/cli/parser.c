#include "cli/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { Main, Arg } cp_state_t;

void cli_parser_new(cli_parser_t *cp, option_t ops[], size_t n) {
  cp->ops = ops;
  cp->n = n;
  cp->args_left = NULL;
}

static option_t *option_search(cli_parser_t *cp, char label) {
  for (size_t i = 0; i < cp->n; i++) {
    if (label == cp->ops[i].label) return &cp->ops[i];
  }
  return NULL;
}

static option_t *loption_search(cli_parser_t *cp, char *llabel) {
  for (size_t i = 0; i < cp->n; i++) {
    if (strcmp(llabel, cp->ops[i].llabel) == 0) return &cp->ops[i];
  }
  return NULL;
}

static void print_usage(cli_parser_t *cp) {
  fprintf(stderr, "Usage:\n");
  for (size_t i = 0; i < cp->n; i++) {
    option_t op = cp->ops[i];
    fprintf(stderr, "\t");
    if (op.label) fprintf(stderr, "-%c", op.label);
    if (op.label && op.llabel) fprintf(stderr, ", ");
    if (op.llabel) fprintf(stderr, "--%s", op.llabel);
    fprintf(stderr, "\n");
  }
}

int cli_parser_parse(cli_parser_t *cp, int argc, char *argv[],
                     void *free_vars[]) {
  cp_state_t state = Main;
  option_t *op = NULL;
  for (int i = 1; i < argc; i++) {
    char *token = calloc(strlen(argv[i]) + 1, sizeof(char));
    strcpy(token, argv[i]);
    token = strtok(token, "=");
    char *arg = strtok(NULL, "=");
    if (state == Main) {
      if (token[0] == '-') {
        if (token[1] == '-') {
          op = loption_search(cp, token + 2);
        } else {
          size_t j;
          for (j = 1; token[j]; j++) {
            op = option_search(cp, token[j]);
            if (op == NULL || op->has_arg) {
              j++;
              break;
            }
          }
          if (op && op->has_arg && token[j]) {
            arg = token + j;
          }
        }
        if (!op) {
          fprintf(stderr, "Cannot find an option '%s'\n", token);
          print_usage(cp);
          free(token);
          return 1;
        }
        if (!op->has_arg)
          op->process(NULL, free_vars);
        else if (arg)
          op->process(arg, free_vars);
        else
          state = Arg;
      } else {
        if (!cp->args_left) {
          cp->args_left = calloc(argc - i + 1, sizeof(char *));
          cp->args_left = NULL;
        }
        char **ptr = cp->args_left;
        while (*ptr) ptr++;
        *ptr = token;
        ptr[1] = NULL;
      }
    } else if (state == Arg) {
      op->process(token, free_vars);
      state = Main;
    }
    // free(token);
  }
  return state != Main;
}

void cli_parser_free(cli_parser_t *cp) {
  if (cp->args_left) {
    free(cp->args_left);
  }
}