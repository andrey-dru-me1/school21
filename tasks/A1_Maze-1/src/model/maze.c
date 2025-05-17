#include "model/maze.h"

#include <stdlib.h>

void maze_new(maze_t *m, size_t h, size_t w) {
  m->grid = calloc(h * w, sizeof(maze_cell_t));
  m->h = h;
  m->w = w;
}

maze_cell_t *maze_cell_get(maze_t *m, size_t row, size_t col) {
  return &m->grid[row * m->w + col];
}

void maze_free(maze_t *m) {
  if (m->grid) {
    free(m->grid);
    m->grid = NULL;
  }
  m->h = 0;
  m->w = 0;
}