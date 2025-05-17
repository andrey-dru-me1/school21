#include <check.h>
#include <stdbool.h>
#include <stdlib.h>

#include "generator/generator.h"
#include "model/maze.h"
#include "model/point.h"
#include "parser/maze_parser.h"
#include "solver/solver.h"

#define APPEND_CELL(D)                        \
  {                                           \
    queue[qi++] = (D);                        \
    marked[mi++] = (D);                       \
    came_from[(D).row * m.w + (D).col] = cur; \
  }

#define CHECK_CELL(D)                                              \
  {                                                                \
    ck_assert_uint_eq(                                             \
        contains(marked, mi, (D)) &&                               \
            !((D).row == came_from[cur.row * m.w + cur.col].row && \
              (D).col == came_from[cur.row * m.w + cur.col].col),  \
        0);                                                        \
  }

static bool contains(point_t *arr, size_t n, point_t e) {
  for (size_t i = 0; i < n; i++) {
    if (arr[i].col == e.col && arr[i].row == e.row) return true;
  }
  return false;
}

START_TEST(test_maze_generator) {
  maze_t m;
  maze_new(&m, 50, 50);
  maze_generator_generate(&m);

  point_t *queue = calloc(m.h * m.w, sizeof(point_t));
  point_t *marked = calloc(m.h * m.w, sizeof(point_t));
  point_t *came_from = calloc(m.h * m.w, sizeof(point_t));
  size_t qi = 0, mi = 0;

  queue[qi++] = (point_t){0, 0};
  marked[mi++] = queue[0];

  while (qi > 0) {
    point_t cur = queue[--qi];

    point_t right = {.row = cur.row, cur.col + 1};
    point_t left = {.row = cur.row, cur.col - 1};
    point_t up = {.row = cur.row - 1, cur.col};
    point_t down = {.row = cur.row + 1, cur.col};

    maze_cell_t *curcell = maze_cell_get(&m, cur.row, cur.col);
    maze_cell_t *leftcell =
        (cur.col > 0) ? maze_cell_get(&m, cur.row, cur.col - 1) : NULL;
    maze_cell_t *upcell =
        (cur.row > 0) ? maze_cell_get(&m, cur.row - 1, cur.col) : NULL;

    if (curcell->right == MazePass) {
      CHECK_CELL(right)
      if (!contains(marked, mi, right)) {
        APPEND_CELL(right)
      }
    }
    if (curcell->down == MazePass) {
      CHECK_CELL(down)
      if (!contains(marked, mi, down)) {
        APPEND_CELL(down)
      }
    }
    if (cur.col > 0 && leftcell->right == MazePass) {
      CHECK_CELL(left)
      if (!contains(marked, mi, left)) {
        APPEND_CELL(left)
      }
    }
    if (cur.row > 0 && upcell->down == MazePass) {
      CHECK_CELL(up)
      if (!contains(marked, mi, up)) {
        APPEND_CELL(up)
      }
    }
  }
  ck_assert_uint_eq(mi, m.h * m.w);

  free(came_from);
  free(queue);
  free(marked);
  maze_free(&m);
}
END_TEST

START_TEST(test_maze_solver) {
  maze_t m;
  maze_file_parser_parse("res/maze1.txt", &m);
  point_t trace[100];
  point_t expected[] = {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1}, {3, 1},
                        {3, 2}, {3, 3}, {4, 3}, {4, 4}, {3, 4}, {3, 5}, {2, 5},
                        {2, 4}, {2, 3}, {1, 3}, {0, 3}, {0, 4}, {1, 4}, {1, 5},
                        {1, 6}, {1, 7}, {2, 7}, {3, 7}, {3, 8}, {2, 8}, {1, 8},
                        {0, 8}, {0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9},
                        {6, 9}, {6, 8}, {5, 8}, {5, 7}, {6, 7}, {6, 6}, {6, 5},
                        {7, 5}, {7, 6}, {8, 6}, {9, 6}, {9, 7}, {9, 8}, {9, 9}};
  size_t expected_len = sizeof(expected) / sizeof(*expected);
  size_t actual_len =
      maze_solver_solve(&m, expected[0], expected[expected_len - 1], trace);
  ck_assert_uint_eq(expected_len, actual_len);
  for (size_t i = 0; i < expected_len; i++) {
    ck_assert_uint_eq(trace[i].row, expected[i].row);
    ck_assert_uint_eq(trace[i].col, expected[i].col);
  }
  maze_free(&m);
}
END_TEST

int main(void) {
  SRunner *sr = srunner_create(NULL);

  Suite *s = suite_create("maze");
  srunner_add_suite(sr, s);

  TCase *tcgen = tcase_create("generator");
  suite_add_tcase(s, tcgen);
  tcase_add_test(tcgen, test_maze_generator);

  TCase *tcsol = tcase_create("solver");
  suite_add_tcase(s, tcsol);
  tcase_add_test(tcsol, test_maze_solver);

  srunner_run_all(sr, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}