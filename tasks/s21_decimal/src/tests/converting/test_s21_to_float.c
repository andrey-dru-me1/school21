#include "../../s21_decimal.h"
#include "test_convert.h"

#define OK 0
#define CONVERTATION_ERR 1

START_TEST(test_s21_to_float_zero) {
  s21_decimal src = {{0, 0, 0, 0}};
  float res;
  float expected = 0.;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &res), OK);
  ck_assert_float_eq(expected, res);
}
END_TEST

START_TEST(test_s21_to_float_ordinary) {
  s21_decimal src = {{156, 0, 0, 2 << 16}};
  float res;
  float expected = 1.56;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &res), OK);
  ck_assert_float_eq_tol(expected, res, 1e-6);
}
END_TEST

START_TEST(test_s21_to_float_ordinary2) {
  s21_decimal src = {
      {0x20000000, 0x7c4a04c2, 0x409f9cbc, (1 << 31) | (28 << 16)}};
  float res;
  float expected = -2.0;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &res), OK);
  ck_assert_float_eq_tol(expected, res, 1e-6);
}
END_TEST

START_TEST(test_s21_to_float_null) {
  s21_decimal src = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_float(src, NULL), CONVERTATION_ERR);
}

TCase *tc_s21_to_float() {
  TCase *tc = tcase_create("s21_to_float");
  tcase_add_test(tc, test_s21_to_float_zero);
  tcase_add_test(tc, test_s21_to_float_null);
  tcase_add_test(tc, test_s21_to_float_ordinary);
  tcase_add_test(tc, test_s21_to_float_ordinary2);
  return tc;
}