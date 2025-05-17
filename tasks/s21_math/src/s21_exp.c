#include <stdio.h>

#include "s21_math.h"

long double s21_exp(double x) {
  long double iterat = 1;
  long double exp_result = 1;
  long double n = 1;
  double eps = 1e-20;

  while (s21_fabs((double)iterat) > eps) {
    iterat *= x / n;
    n += 1;
    exp_result += iterat;
    if (exp_result > __DBL_MAX__) {
      exp_result = S21_INF;
      break;
    }
  }
  return exp_result;
}