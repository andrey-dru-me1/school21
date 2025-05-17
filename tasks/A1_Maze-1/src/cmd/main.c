#include <locale.h>
#include <ncurses.h>

#include "cli/parser.h"
#include "cmd/cave_subcmd.h"
#include "cmd/cli_processor.h"
#include "cmd/maze/subcmd.h"
#include "model/app.h"

static void init_curses() {
  setlocale(LC_ALL, "");
  WINDOW *stdscr = initscr();
  cbreak();
  curs_set(0);
  noecho();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  start_color();
  refresh();
}

int main(int argc, char *argv[]) {
  app_t app;
  app_new(&app);
  int res = cli_processor_process(argc, argv, &app);
  if (res) {
    app_free(&app);
    return res;
  }

  init_curses();

  if (app.mt == MTCave) {
    res = cave_subcmd(&app);
  } else if (app.mt == MTMaze) {
    res = maze_subcmd(&app);
  }
  endwin();

  app_free(&app);
  return res;
}
