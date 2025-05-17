#include "cmd/maze/win_printer.h"

#include <curses.h>

#include "solver/solver.h"

void win_printer_print(event_loop_t *el) {
  clear();
  refresh();

  if (el->s == AppShowBounds) {
    mvprintw(0, 0, "Size of terminal is too small for displaying a trace.");
    mvprintw(5, 0, "Terminal size is: %lux%lu. You need at least: %lux%lu.",
             el->mp.winh, el->mp.winw, el->m->h * 2 + 1, el->m->w * 2 + 1);
  } else {
    if (el->mp.ch > 0 && el->mp.cw > 0) {
      maze_printer_print(&el->mp);
    } else {
      mvprintw(0, 0,
               "Size of terminal is too small for displaying current maze.");
      mvprintw(5, 0, "Terminal size is: %lux%lu. You need at least: %lux%lu.",
               el->mp.winh, el->mp.winw, el->m->h + 1, el->m->w + 1);
    }

    if (el->s == AppMain && el->beginset && el->finishset) {
      size_t tracelen =
          maze_solver_solve(el->m, el->begin, el->finish, el->trace);
      maze_printer_print_trace(&el->mp, el->trace, tracelen);
    }

    if (el->beginset) {
      wattron(el->mp.win, COLOR_PAIR(4));
      mvwaddch(el->mp.win, el->begin.row * el->mp.ch + el->mp.ch / 2,
               el->begin.col * el->mp.cw + el->mp.cw / 2, ' ');
      wattroff(el->mp.win, COLOR_PAIR(4));
    }

    if (el->finishset) {
      wattron(el->mp.win, COLOR_PAIR(5));
      mvwaddch(el->mp.win, el->finish.row * el->mp.ch + el->mp.ch / 2,
               el->finish.col * el->mp.cw + el->mp.cw / 2, ' ');
      wattroff(el->mp.win, COLOR_PAIR(5));
    }

    if (el->s == AppSelectBegin || el->s == AppSelectFinish) {
      wattron(el->mp.win, COLOR_PAIR(3));
      mvwaddch(el->mp.win, el->pos.row * el->mp.ch + el->mp.ch / 2,
               el->pos.col * el->mp.cw + el->mp.cw / 2, ' ');
      wattroff(el->mp.win, COLOR_PAIR(3));
    }
  }

  wrefresh(el->mp.win);
}