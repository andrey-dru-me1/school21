#include "cmd/maze/subcmd.h"

#include <stdlib.h>

#include "cmd/maze/internal.h"
#include "cmd/maze/user_handler.h"
#include "cmd/maze/win_printer.h"
#include "generator/generator.h"
#include "model/app.h"
#include "parser/maze_parser.h"
#include "saver/saver.h"

static void init_color_pairs() {
  init_pair(3, COLOR_WHITE, COLOR_WHITE);
  init_pair(4, COLOR_WHITE, COLOR_YELLOW);
  init_pair(5, COLOR_WHITE, COLOR_RED);
}

static void event_loop(maze_t *m) {
  event_loop_t el = {.m = m,
                     .s = AppMain,
                     .begin = {0, 0},
                     .finish = {m->h - 1, m->w - 1},
                     .pos = {0, 0},
                     .beginset = false,
                     .finishset = false,
                     .loop = true};

  maze_printer_new(&el.mp, el.m);
  el.trace = calloc(m->h * m->w, sizeof(point_t));

  init_color_pairs();

  while (el.loop) {
    win_printer_print(&el);
    user_handler_handle(&el);
  }
  free(el.trace);
  maze_printer_free(&el.mp);
}

int maze_subcmd(app_t *app) {
  maze_t m = {0};
  if (app->infname) {
    maze_file_parser_parse(app->infname, &m);
  } else if (app->generate) {
    maze_new(&m, app->h, app->w);
    maze_generator_generate(&m);
  }
  if (m.h > 50 || m.w > 50) {
    mvprintw(0, 0, "Maze size should match bounds 50x50 but it is %lux%lu\n",
             m.h, m.w);
    getch();
  } else {
    event_loop(&m);
    if (app->outfname) maze_saver_save(&m, app->outfname);
  }

  maze_free(&m);
  return 0;
}