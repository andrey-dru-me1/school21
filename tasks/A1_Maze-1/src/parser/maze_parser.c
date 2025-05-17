#include "parser/maze_parser.h"

#include <stdint.h>
#include <stdio.h>

#include "parser/file_parser.h"

typedef enum { Bounds, Rights, Bottoms, Term } parse_state_t;

typedef parse_state_t (*transition_fn)(char *token, maze_t *m, size_t *i,
                                       size_t *j);

static parse_state_t parse_bounds(char *token, maze_t *m, size_t *, size_t *j) {
  size_t bound;
  sscanf(token, "%lu", &bound);

  parse_state_t ret_state;
  if (*j == 0) {
    m->h = bound;
    (*j)++;
    ret_state = Bounds;
  } else {
    m->w = bound;
    *j = 0;
    maze_new(m, m->h, m->w);
    ret_state = Rights;
  }
  return ret_state;
}

static parse_state_t parse_bottoms(char *token, maze_t *m, size_t *i,
                                   size_t *j) {
  if (*j >= m->w) {
    (*i)++;
    *j = 0;
  }
  if (*i >= m->h) {
    *i = 0;
    *j = 0;
    return Term;
  }

  uint8_t bottom;
  sscanf(token, "%hhu", &bottom);
  if (bottom == 1)
    maze_cell_get(m, *i, *j)->down = MazeWall;
  else
    maze_cell_get(m, *i, *j)->down = MazePass;
  (*j)++;
  return Bottoms;
}

static parse_state_t parse_rights(char *token, maze_t *m, size_t *i,
                                  size_t *j) {
  if (*j >= m->w) {
    (*i)++;
    *j = 0;
  }
  if (*i >= m->h) {
    *i = 0;
    *j = 0;
    return parse_bottoms(token, m, i, j);
  }

  uint8_t right;
  sscanf(token, "%hhu", &right);
  if (right == 1)
    maze_cell_get(m, *i, *j)->right = MazeWall;
  else
    maze_cell_get(m, *i, *j)->right = MazePass;
  (*j)++;
  return Rights;
}

static parse_state_t pass(char *, maze_t *, size_t *, size_t *) { return Term; }

static void process_token(char *token, void *args[]) {
  static transition_fn ts[] = {parse_bounds, parse_rights, parse_bottoms,
                               pass};  // transitions

  maze_t *m = args[0];
  parse_state_t *state = args[1];
  size_t *i = args[2];
  size_t *j = args[3];
  *state = ts[*state](token, m, i, j);
}

void maze_file_parser_parse(char *fname, maze_t *m) {
  parse_state_t state = Bounds;
  size_t i = 0, j = 0;
  file_parser_parse(fname, process_token, (void *[]){m, &state, &i, &j});
}