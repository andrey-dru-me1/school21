#include <stdbool.h>

#include "../s21_decimal.h"
#include "arithm/utils/utils.h"
#include "uint_n_arithm/uint_n_arithm.h"
#include "utils/utils.h"

#define FALSE 0
#define TRUE 1

static void shift_until_overflow(s21_decimal *a, int *a_exp) {
  s21_decimal v = *a, prev = v;
  int v_exp = *a_exp;
  while (s21_uint_n_mul(v.bits, 3, 10, false, v.bits) == 0) {
    v_exp++;
    prev = v;
  }

  *a_exp = v_exp - 1;
  *a = prev;
}

static char s21_cmp(s21_decimal a, s21_decimal b) {
  if (is_zero(a.bits, 3) && is_zero(b.bits, 3)) return 0;
  if (is_zero(a.bits, 3)) return is_positive(&b) ? -1 : 1;
  if (is_zero(b.bits, 3)) return is_negative(&a) ? -1 : 1;
  int res = 0;

  if (is_negative(&a) && is_positive(&b))
    res = -1;
  else if (is_positive(&a) && is_negative(&b))
    res = 1;
  else {
    char sign = is_negative(&a) ? -1 : 1;
    int a_exp = get_exp(&a), b_exp = get_exp(&b);
    shift_until_overflow(&a, &a_exp);
    shift_until_overflow(&b, &b_exp);
    if (a_exp != b_exp)
      res = a_exp > b_exp ? -sign : sign;
    else
      res = sign * s21_uint_n_cmp(a.bits, 3, b.bits, 3);
  }

  return res;
}

int s21_is_less(s21_decimal a, s21_decimal b) { return s21_cmp(a, b) < 0; }

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_cmp(a, b) <= 0;
}

int s21_is_greater(s21_decimal a, s21_decimal b) { return s21_cmp(a, b) > 0; }

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return s21_cmp(a, b) >= 0;
}

int s21_is_equal(s21_decimal a, s21_decimal b) { return s21_cmp(a, b) == 0; }

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return s21_cmp(a, b) != 0;
}
