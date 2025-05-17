#ifndef C83E194B_181C_4D48_973F_C0623E9E7730
#define C83E194B_181C_4D48_973F_C0623E9E7730

#include "model/maze.h"
#include "model/point.h"
#include "tui/maze_printer.h"

typedef enum {
  AppMain,
  AppSelectBegin,
  AppSelectFinish,
  AppShowBounds
} app_state_t;

typedef struct {
  maze_t *m;
  point_t *trace;
  maze_printer_t mp;
  point_t pos;
  point_t begin, finish;
  app_state_t s;
  bool beginset, finishset;
  bool loop;
} event_loop_t;

#endif /* C83E194B_181C_4D48_973F_C0623E9E7730 */
