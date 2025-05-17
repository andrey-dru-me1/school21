#include "saver/saver.h"

#include <stdio.h>

void maze_saver_save(maze_t *m, char *fname) {
  FILE *f = fopen(fname, "w+");

  fprintf(f, "%lu %lu\n", m->h, m->w);

  for (size_t i = 0; i < m->h; i++) {
    for (size_t j = 0; j < m->w - 1; j++) {
      fprintf(f, "%hu ", (maze_cell_get(m, i, j)->right == MazeWall) ? 1 : 0);
    }
    fprintf(f, "%hu\n",
            (maze_cell_get(m, i, m->w - 1)->right == MazeWall) ? 1 : 0);
  }

  fprintf(f, "\n");

  for (size_t i = 0; i < m->h; i++) {
    for (size_t j = 0; j < m->w - 1; j++) {
      fprintf(f, "%hu ", (maze_cell_get(m, i, j)->down == MazeWall) ? 1 : 0);
    }
    fprintf(f, "%hu\n",
            (maze_cell_get(m, i, m->w - 1)->down == MazeWall) ? 1 : 0);
  }

  fclose(f);
}