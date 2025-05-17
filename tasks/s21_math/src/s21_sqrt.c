#include "s21_math.h"

long double s21_sqrt(double x) {
  if (x == S21_NAN || x < 0)
    return S21_NAN;
  else if (x == S21_INF)
    return S21_INF;
  else if (x == 0.)
    return 0.;

  long double a = x;
  for (int i = 0; i < 50; i++) {
    a = (a + x / a) / 2;
  }
  return a;
}