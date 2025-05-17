#include "s21_math.h"

long double s21_log(double x) {
  if (x == 0.0) {
    return -S21_INF;
  }

  if (x < 0.0) {
    return S21_NAN;
  }

  double result = 0;
  double before_value = 0;

  for (int i = 0; i < 1000; i++) {
    before_value = result;
    result = before_value +
             2 * (x - s21_exp(before_value)) / (x + s21_exp(before_value));
  }

  return result;
}