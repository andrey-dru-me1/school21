#include "model/cave.h"

#include <stdlib.h>

void cave_new(cave_t *c, size_t h, size_t w) {
  c->grid = calloc(h * w, sizeof(cave_cell_t));
  c->h = h;
  c->w = w;
}

cave_cell_t *cave_cell_get(cave_t *c, size_t row, size_t col) {
  return &c->grid[row * c->w + col];
}

void cave_free(cave_t *c) {
  if (c->grid) {
    free(c->grid);
    c->grid = NULL;
  }
  c->h = 0;
  c->w = 0;
}