#ifndef A8FFA4EF_A22C_429A_9ACB_9B222F0C7DB7
#define A8FFA4EF_A22C_429A_9ACB_9B222F0C7DB7

#include "model/maze.h"
#include "model/point.h"

size_t maze_solver_solve(maze_t *m, point_t begin, point_t finish,
                         point_t *trace);

#endif /* A8FFA4EF_A22C_429A_9ACB_9B222F0C7DB7 */
