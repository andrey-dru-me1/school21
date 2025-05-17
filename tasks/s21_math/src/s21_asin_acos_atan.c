#include "s21_math.h"

static long double s21_atanl(long double x) {
  long double sqrt_3 = s21_sqrt(3.);
  if (x < 0.) return -s21_atanl(-x);
  if (x == 0.) return x;
  if (x > 1.) return PI / 2. - s21_atanl(1. / x);
  if (x == 1.) return PI / 4.;
  if (x >= 0.26795)
    return PI / 6. + s21_atanl((x * sqrt_3 - 1.) / (x + sqrt_3));

  long double res = 0.;
  const long double sq_x = (long double)x * x;
  const unsigned start_n = 14;
  char sign = (start_n % 2 == 0 ? 1 : -1);
  for (unsigned n = start_n * 2 + 1; n >= 3; n -= 2) {
    res = res * sq_x + (long double)sign / n;

    sign = -sign;
  }
  return x + x * sq_x * res;
}

long double s21_atan(double x) { return s21_atanl(x); }

long double s21_asin(double x) {
  long double lx = x;
  return s21_atanl(lx / s21_sqrt(1 - lx * lx));
}

long double s21_acos(double x) { return PI / 2. - s21_asin(x); }
