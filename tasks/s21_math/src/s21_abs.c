#include "s21_math.h"

int s21_abs(int x) {
  x = (x >= 0) ? x : (-x);
  return x;
}