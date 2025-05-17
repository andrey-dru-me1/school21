#include "cmd/cave_subcmd.h"

#include <curses.h>

#include "model/app.h"
#include "model/cave.h"
#include "parser/cave_parser.h"
#include "tui/cave_printer.h"

int cave_subcmd(app_t *app) {
  cave_t c = {0};
  if (app->infname) cave_file_parser_parse(app->infname, &c);
  cave_printer_print(&c);
  cave_free(&c);
  getch();
  return 0;
}