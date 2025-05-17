#include "parser/cave_parser.h"

#include <stdint.h>
#include <stdio.h>

#include "parser/file_parser.h"

typedef enum { Bounds, Grid, Term } parse_state_t;

static void process_token(char *token, void *args[]) {
  cave_t *c = args[0];
  parse_state_t *state = args[1];
  size_t *i = args[2];
  size_t *j = args[3];

  switch (*state) {
    case Bounds:
      size_t bound;
      sscanf(token, "%lu", &bound);
      if (*j == 0) {
        c->h = bound;
        (*j)++;
        *state = Bounds;
      } else {
        cave_new(c, c->h, bound);
        *j = 0;
        *state = Grid;
      }
      break;
    case Grid:
      if (*j >= c->w) {
        (*i)++;
        *j = 0;
      }
      if (*i >= c->h) {
        *i = *j = 0;
        *state = Term;
        break;
      }

      uint8_t cell;
      sscanf(token, "%hhu", &cell);
      *cave_cell_get(c, *i, *j) = (cell == 1) ? CaveBlock : CavePass;
      (*j)++;
      break;
    default:
      break;
  }
}

void cave_file_parser_parse(char *fname, cave_t *c) {
  parse_state_t state = Bounds;
  size_t i = 0, j = 0;
  file_parser_parse(fname, process_token, (void *[]){c, &state, &i, &j});
}
