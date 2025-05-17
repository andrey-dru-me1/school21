#include "tui/cave_printer.h"

#include <curses.h>

void cave_printer_print(cave_t *c) {
  init_pair(1, COLOR_WHITE, COLOR_WHITE);

  size_t ch, cw, winh, winw;
  getmaxyx(stdscr, winh, winw);
  ch = (winh - 2) / c->h;
  cw = (winw - 2) / c->w;

  if (ch > 0 && cw > 0) {
    WINDOW *cave_win =
        newwin(c->h * ch + 2, c->w * cw + 2, (winh - (c->h * ch + 2)) / 2,
               (winw - (c->w * cw + 2)) / 2);
    wclear(cave_win);
    box(cave_win, 0, 0);

    wattron(cave_win, COLOR_PAIR(1));

    for (size_t i = 0; i < c->h; i++) {
      for (size_t j = 0; j < c->w; j++) {
        if (*cave_cell_get(c, i, j) == CaveBlock)
          for (size_t ih = i * ch + 1; ih < (i + 1) * ch + 1; ih++)
            for (size_t iw = j * cw + 1; iw < (j + 1) * cw + 1; iw++)
              mvwaddch(cave_win, ih, iw, ' ');
      }
    }

    wattroff(cave_win, COLOR_PAIR(1));
    wrefresh(cave_win);
  } else {
    mvprintw(0, 0,
             "Size of terminal is too small for displaying current cave.");
    mvprintw(5, 0, "Terminal size is: %lux%lu. You need at least: %lux%lu.",
             winh, winw, c->h + 2, c->w + 2);
  }
}