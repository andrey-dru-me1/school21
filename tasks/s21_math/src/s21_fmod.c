#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double result = S21_NAN;
  if (y != 0.0 && !S21_IS_NAN(x) && !S21_IS_NAN(y) && !S21_IS_INF(x)) {
    if (!S21_IS_INF(y)) {
      long long n = (long long)(x / y);
      result = x - n * y;
    } else
      result = x;
  }
  return result;
}
