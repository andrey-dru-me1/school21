#ifndef B711AA8C_1A8C_460D_A2B0_3BB0B357B133
#define B711AA8C_1A8C_460D_A2B0_3BB0B357B133

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  void (*process)(char *token, void *args[]);
  char *llabel;
  char label;
  bool has_arg;
} option_t;

typedef struct {
  option_t *ops;
  char **args_left;
  size_t n;
} cli_parser_t;

void cli_parser_new(cli_parser_t *cp, option_t ops[], size_t n);

int cli_parser_parse(cli_parser_t *cp, int argc, char *argv[],
                     void *free_vars[]);

void cli_parser_free(cli_parser_t *cp);

#endif /* B711AA8C_1A8C_460D_A2B0_3BB0B357B133 */
