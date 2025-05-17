#include "s21_math.h"

long double s21_floor(double x) {
  long double result = x;
  if (!S21_IS_NAN(x) && !S21_IS_INF(x)) {
    if (x - (long long)x < 0) x--;
    result = (long long)x;
  }
  return result;
}
