#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result;

  if (base == 0 && exp != 0) return 0.0;

  if (base == 0 && exp == 0) return 1.0;

  if (base < 0 && exp != s21_floor(exp)) return S21_NAN;

  if (base > 0) {
    result = s21_exp(exp * s21_log(base));
  } else {
    base = -base;
    result = s21_exp(exp * s21_log(base));
    if (s21_fmod(exp, 2) != 0) {
      result = -result;
    }
  }
  return result;
}