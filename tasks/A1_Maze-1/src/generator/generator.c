#include "generator/generator.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** The `set_info_t` struct is used for counting cells with bottom walls.
 * For each set, we need to have at least one pass to the underlying row. The
 * struct provides the set id `set_no`, the total quantity of cells contained
 * in the set `n` and the quantity of bottom walls `bottom_cnt`.
 */
typedef struct {
  size_t set_no;      // set number
  size_t bottom_cnt;  // quantity of bottom walls for the set number
  size_t n;           // total quantity of cells for the set number
} set_info_t;

static void zero_maze(maze_t *m) {
  for (size_t i = 0; i < m->h; i++) {
    for (size_t j = 0; j < m->w; j++) {
      *maze_cell_get(m, i, j) = (maze_cell_t){MazePass, MazePass};
    }
  }
}

static void arrange_walls(maze_t *m, size_t i, size_t *id, size_t *row) {
  for (size_t j = 0; j < m->w; j++) {
    maze_cell_t *cur = maze_cell_get(m, i, j);
    maze_cell_t *left = (j > 0) ? maze_cell_get(m, i, j - 1) : 0;

    if (row[j] == 0) row[j] = (*id)++;  // identify cells without any set

    // set right wall either between united cells or randomly
    if (j > 0 && (row[j - 1] == row[j] || (rand() % 3) == 0)) {
      left->right = MazeWall;
    }

    // unite cells without a wall between them into one set
    if (j > 0 && left->right == MazePass) {
      size_t prev = row[j];
      for (size_t k = 0; k < m->w; k++) {
        if (row[k] == prev) {
          row[k] = row[j - 1];
        }
      }
    }

    // set bottom wall randomly
    if (rand() % 2 == 0) cur->down = MazeWall;
  }
}

static size_t fill_setinfo(maze_t *m, size_t i, set_info_t *si, size_t *row) {
  memset(si, 0, m->w);
  size_t si_idx = 0;

  // collect information about each set: its cell amount and cell with bottom
  // wall amount
  for (size_t j = 0; j < m->w; j++) {
    maze_cell_t *cur = maze_cell_get(m, i, j);

    // search for an existing record aboud current set number
    bool found = false;
    for (size_t k = 0; !found && k < si_idx; k++) {
      if (si[k].set_no == row[j]) {
        found = true;
        si[k].n++;
        if (cur->down == MazeWall) si[k].bottom_cnt++;
      }
    }

    // create new record if such does not exist
    if (found == false) {
      si[si_idx++] =
          (set_info_t){.set_no = row[j],
                       .n = 1,
                       .bottom_cnt = (cur->down == MazeWall) ? 1 : 0};
    }
  }
  return si_idx;
}

static void fix_bottom_walls(maze_t *m, size_t i, set_info_t *si, size_t si_len,
                             size_t *row) {
  // validate if each set has at least one pass to the underlying row
  for (size_t k = 0; k < si_len; k++) {
    // if not - create such
    if (si[k].n == si[k].bottom_cnt) {
      size_t out = rand() % si[k].bottom_cnt;
      size_t kj = 0;
      for (size_t j = 0; kj <= out && j < m->w; j++) {
        if (row[j] == si[k].set_no) {
          if (out == kj) maze_cell_get(m, i, j)->down = MazePass;
          kj++;
        }
      }
    }
  }
}

static void zero_underwall_cells(maze_t *m, size_t i, size_t *row) {
  // remove cells from any set if they are separated from the upper cell by
  // a wall
  for (size_t j = 0; j < m->w; j++) {
    maze_cell_t *cur = maze_cell_get(m, i, j);
    if (cur->down == MazeWall) row[j] = 0;
  }
}

static void process_last_row_walls(maze_t *m, size_t *row) {
  // break walls between cells from distinct sets on the last row to create a
  // fully traversable maze
  for (size_t j = 0; j < m->w - 1; j++) {
    maze_cell_t *cur = maze_cell_get(m, m->h - 1, j);
    if (row[j] != row[j + 1]) {
      cur->right = MazePass;
      size_t prev = row[j + 1];
      for (size_t k = 0; k < m->w; k++)
        if (row[k] == prev) row[k] = row[j];
    }
  }
}

static void set_outer_walls(maze_t *m) {
  for (size_t i = 0; i < m->h; i++)
    maze_cell_get(m, i, m->w - 1)->right = MazeWall;
  for (size_t i = 0; i < m->w; i++)
    maze_cell_get(m, m->h - 1, i)->down = MazeWall;
}

void maze_generator_generate(maze_t *m) {
  srand(time(NULL));

  zero_maze(m);

  set_info_t *setinfo = calloc(m->w, sizeof(set_info_t));
  size_t *row = calloc(m->w, sizeof(size_t));
  size_t id = 1;
  for (size_t i = 0; i < m->h - 1; i++) {
    arrange_walls(m, i, &id, row);
    size_t si_len = fill_setinfo(m, i, setinfo, row);
    fix_bottom_walls(m, i, setinfo, si_len, row);
    zero_underwall_cells(m, i, row);
  }
  arrange_walls(m, m->h - 1, &id, row);
  process_last_row_walls(m, row);
  set_outer_walls(m);

  free(setinfo);
  free(row);
}