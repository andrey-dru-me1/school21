#include "cmd/maze/user_handler.h"

typedef enum { Quit, Down, Up, Left, Right, Enter } act_t;

static app_state_t quit(event_loop_t *el) {
  el->loop = false;
  return el->s;
}

static app_state_t enter_selbeg_state(event_loop_t *el) {
  if (el->mp.ch <= 1 || el->mp.cw <= 1) {
    return AppShowBounds;
  }
  el->beginset = false;
  el->pos = el->begin;
  return AppSelectBegin;
}

static app_state_t select_begin(event_loop_t *el) {
  el->begin = el->pos;
  el->beginset = true;
  el->finishset = false;
  el->pos = el->finish;
  return AppSelectFinish;
}

static app_state_t select_finish(event_loop_t *el) {
  el->finishset = true;
  el->finish = el->pos;
  return AppMain;
}

static app_state_t down(event_loop_t *el) {
  el->pos.row = (el->pos.row + 1) % el->m->h;
  return el->s;
}

static app_state_t up(event_loop_t *el) {
  el->pos.row = (el->m->h + el->pos.row - 1) % el->m->h;
  return el->s;
}

static app_state_t left(event_loop_t *el) {
  el->pos.col = (el->m->w + el->pos.col - 1) % el->m->w;
  return el->s;
}

static app_state_t right(event_loop_t *el) {
  el->pos.col = (el->pos.col + 1) % el->m->w;
  return el->s;
}

static app_state_t back(event_loop_t *) { return AppMain; }

static app_state_t pass(event_loop_t *el) { return el->s; }

static void fsm(event_loop_t *el, act_t act) {
  typedef app_state_t (*transition_fn)(event_loop_t *el);
  static transition_fn transitions[][6] = {
      {quit, pass, pass, pass, pass, enter_selbeg_state},  // Main
      {quit, down, up, left, right, select_begin},         // SelectBegin
      {quit, down, up, left, right, select_finish},        // SelectFinish
      {quit, back, back, back, back, back}                 // ShowBounds
  };
  el->s = transitions[el->s][act](el);
}

void user_handler_handle(event_loop_t *el) {
  int c = getch();
  act_t act;
  switch (c) {
    case 'q':
      act = Quit;
      break;
    case '\n':
      act = Enter;
      break;
    case KEY_UP:
      act = Up;
      break;
    case KEY_DOWN:
      act = Down;
      break;
    case KEY_LEFT:
      act = Left;
      break;
    case KEY_RIGHT:
      act = Right;
      break;
    default:
      return;
  }
  fsm(el, act);
}