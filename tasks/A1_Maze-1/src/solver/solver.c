#include "solver/solver.h"

#include <stdbool.h>
#include <stdlib.h>

#define APPEND_CELL(D)                         \
  {                                            \
    queue[qi++] = (D);                         \
    marked[mi++] = (D);                        \
    came_from[(D).row * m->w + (D).col] = cur; \
  }

static bool contains(point_t *arr, size_t n, point_t e) {
  for (size_t i = 0; i < n; i++) {
    if (arr[i].col == e.col && arr[i].row == e.row) return true;
  }
  return false;
}

size_t maze_solver_solve(maze_t *m, point_t begin, point_t finish,
                         point_t *trace) {
  point_t *queue = calloc(m->h * m->w, sizeof(point_t));
  point_t *marked = calloc(m->h * m->w, sizeof(point_t));
  point_t *came_from = calloc(m->h * m->w, sizeof(point_t));
  size_t qi = 0, mi = 0;

  queue[qi++] = begin;
  marked[mi++] = begin;

  while (qi > 0) {
    point_t cur = queue[--qi];

    if (cur.row == finish.row && cur.col == finish.col) break;

    point_t right = {.row = cur.row, cur.col + 1};
    point_t left = {.row = cur.row, cur.col - 1};
    point_t up = {.row = cur.row - 1, cur.col};
    point_t down = {.row = cur.row + 1, cur.col};

    maze_cell_t *curcell = maze_cell_get(m, cur.row, cur.col);
    maze_cell_t *leftcell =
        (cur.col > 0) ? maze_cell_get(m, cur.row, cur.col - 1) : NULL;
    maze_cell_t *upcell =
        (cur.row > 0) ? maze_cell_get(m, cur.row - 1, cur.col) : NULL;

    if (curcell->right == MazePass && !contains(marked, mi, right))
      APPEND_CELL(right)
    if (curcell->down == MazePass && !contains(marked, mi, down))
      APPEND_CELL(down)
    if (cur.col > 0 && leftcell->right == MazePass &&
        !contains(marked, mi, left))
      APPEND_CELL(left)
    if (cur.row > 0 && upcell->down == MazePass && !contains(marked, mi, up))
      APPEND_CELL(up)
  }

  size_t len = 0;
  for (point_t cur = finish; !(cur.row == begin.row && cur.col == begin.col);
       cur = came_from[cur.row * m->w + cur.col]) {
    trace[len++] = cur;
  }
  trace[len++] = begin;

  for (size_t i = 0; i < len / 2; i++) {
    point_t c = trace[i];
    trace[i] = trace[len - i - 1];
    trace[len - i - 1] = c;
  }

  free(came_from);
  free(queue);
  free(marked);
  return len;
}
