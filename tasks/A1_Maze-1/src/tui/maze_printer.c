#include "tui/maze_printer.h"

void maze_printer_new(maze_printer_t *mp, maze_t *m) {
  mp->m = m;

  getmaxyx(stdscr, mp->winh, mp->winw);
  mp->ch = (mp->winh - 1) / m->h;
  mp->cw = (mp->winw - 1) / m->w;
  mp->win = newwin(m->h * mp->ch + 1, m->w * mp->cw + 1,
                   (mp->winh - (m->h * mp->ch + 1)) / 2,
                   (mp->winw - (m->w * mp->cw + 1)) / 2);
}

static chtype choose_symbol(bool left, bool up, bool right, bool down) {
  chtype res = ' ';
  if (up && down && left && right)
    res = ACS_PLUS;
  else if (up && down && left)
    res = ACS_RTEE;
  else if (up && down && right)
    res = ACS_LTEE;
  else if (up && left && right)
    res = ACS_BTEE;
  else if (down && left && right)
    res = ACS_TTEE;
  else if (up && right)
    res = ACS_LLCORNER;
  else if (up && left)
    res = ACS_LRCORNER;
  else if (down && right)
    res = ACS_ULCORNER;
  else if (down && left)
    res = ACS_URCORNER;
  else if (up || down)
    res = ACS_VLINE;
  else if (left || right)
    res = ACS_HLINE;
  return res;
}

static chtype calc_symbol(maze_t *m, size_t i, size_t j) {
  bool upline =
      i != 0 && (j == 0 || maze_cell_get(m, i - 1, j - 1)->right == MazeWall);
  bool downline =
      i != m->h && (j == 0 || maze_cell_get(m, i, j - 1)->right == MazeWall);
  bool leftline =
      j != 0 && (i == 0 || maze_cell_get(m, i - 1, j - 1)->down == MazeWall);
  bool rightline =
      j != m->w && (i == 0 || maze_cell_get(m, i - 1, j)->down == MazeWall);
  return choose_symbol(leftline, upline, rightline, downline);
}

void maze_printer_print(maze_printer_t *mp) {
  wclear(mp->win);
  box(mp->win, 0, 0);

  for (size_t i = 0; i < mp->m->h; i++) {
    for (size_t j = 0; j < mp->m->w; j++) {
      maze_cell_t mc = *maze_cell_get(mp->m, i, j);
      if (mc.down == MazeWall) {
        for (size_t k = j * mp->cw + 1; k < (j + 1) * mp->cw; k++)
          mvwaddch(mp->win, (i + 1) * mp->ch, k, ACS_HLINE);
      }
      if (mc.right == MazeWall)
        for (size_t k = i * mp->ch + 1; k < (i + 1) * mp->ch; k++)
          mvwaddch(mp->win, k, (j + 1) * mp->cw, ACS_VLINE);
    }
  }
  for (size_t i = 0; i <= mp->m->h; i++) {
    for (size_t j = 0; j <= mp->m->w; j++) {
      mvwaddch(mp->win, i * mp->ch, j * mp->cw, calc_symbol(mp->m, i, j));
    }
  }
  wrefresh(mp->win);
}

void maze_printer_print_trace(maze_printer_t *mp, point_t *trace, size_t len) {
  init_pair(2, COLOR_RED, COLOR_BLACK);
  wattron(mp->win, COLOR_PAIR(2));

  size_t vshift = (mp->ch) / 2, hshift = (mp->cw) / 2;
  for (size_t i = 0; i < len; i++) {
    point_t cur = trace[i];

    bool leftline = (i > 0 && trace[i - 1].col < trace[i].col) ||
                    (i < len - 1 && trace[i + 1].col < trace[i].col);
    bool rightline = (i > 0 && trace[i - 1].col > trace[i].col) ||
                     (i < len - 1 && trace[i + 1].col > trace[i].col);
    bool upline = (i > 0 && trace[i - 1].row < trace[i].row) ||
                  (i < len - 1 && trace[i + 1].row < trace[i].row);
    bool downline = (i > 0 && trace[i - 1].row > trace[i].row) ||
                    (i < len - 1 && trace[i + 1].row > trace[i].row);
    mvwaddch(mp->win, cur.row * mp->ch + vshift, cur.col * mp->cw + hshift,
             choose_symbol(leftline, upline, rightline, downline));
    if (rightline) {
      for (size_t j = cur.col * mp->cw + hshift + 1;
           j < cur.col * mp->cw + hshift + mp->cw; j++) {
        mvwaddch(mp->win, cur.row * mp->ch + vshift, j, ACS_HLINE);
      }
    }
    if (downline) {
      for (size_t j = cur.row * mp->ch + vshift + 1;
           j < cur.row * mp->ch + vshift + mp->ch; j++) {
        mvwaddch(mp->win, j, cur.col * mp->cw + hshift, ACS_VLINE);
      }
    }
  }

  wattroff(mp->win, COLOR_PAIR(2));
  wrefresh(mp->win);
}

void maze_printer_free(maze_printer_t *mp) { delwin(mp->win); }