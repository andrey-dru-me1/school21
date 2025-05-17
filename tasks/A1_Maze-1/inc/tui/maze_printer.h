#ifndef C8D69413_507C_4E77_9901_5B77E86FE25F
#define C8D69413_507C_4E77_9901_5B77E86FE25F

#include <curses.h>

#include "model/maze.h"
#include "model/point.h"

typedef struct {
  maze_t *m;
  WINDOW *win;
  size_t winh, winw, ch, cw;
} maze_printer_t;

void maze_printer_new(maze_printer_t *mp, maze_t *m);

void maze_printer_print(maze_printer_t *mp);

void maze_printer_print_trace(maze_printer_t *mp, point_t *trace, size_t len);

void maze_printer_free(maze_printer_t *mp);

#endif /* C8D69413_507C_4E77_9901_5B77E86FE25F */
