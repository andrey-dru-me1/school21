#include <stdio.h>

#include "s21_math.h"

static long long unsigned fact[] = {1UL,
                                    1UL,
                                    2UL,
                                    6UL,
                                    24UL,
                                    120UL,
                                    720UL,
                                    5040UL,
                                    40320UL,
                                    362880UL,
                                    3628800UL,
                                    39916800UL,
                                    479001600UL,
                                    6227020800UL,
                                    87178291200UL,
                                    1307674368000UL,
                                    20922789888000UL,
                                    355687428096000UL,
                                    6402373705728000UL,
                                    121645100408832000UL};

static long double limit_x(long double x) {
  while (x > PI) {
    x -= 2 * PI;
  }
  while (x < -PI) {
    x += 2 * PI;
  }
  return x;
}

static long double compute_mcloren(long double x, int first_n, int last_n) {
  long double res = 0.;
  char sign = (last_n % 4 < 2 ? 1 : -1);
  const long double xx = x * x;
  for (int n = last_n; n >= first_n; n -= 2) {
    res = res * xx + (long double)sign / fact[n];
    sign = -sign;
  }
  return res;
}

static long double s21_cosl(long double x);

#define ACC 0.01

static long double s21_sinl(long double x) {
  x = limit_x(x);
  if (x > ACC || x < -ACC) {
    return 2 * s21_sinl(x / 2) * s21_cosl(x / 2);
  }
  return x + x * x * x * compute_mcloren(x, 3, 19);
}

static long double s21_cosl(long double x) {
  x = limit_x(x);
  if (x > ACC || x < -ACC) {
    long double cos_res = s21_cosl(x / 2);
    long double sin_res = s21_sinl(x / 2);
    return cos_res * cos_res - sin_res * sin_res;
  }
  return compute_mcloren(x, 0, 18);
}

#undef ACC

long double s21_sin(double x) { return s21_sinl(x); }

long double s21_cos(double x) { return s21_cosl(x); }

long double s21_tan(double x) {
  long double result = s21_sin(x) / s21_cos(x);
  return result;
}
