#include "../../s21_decimal.h"
#include "../string_converter/string_converter.h"
#include "test_convert.h"

START_TEST(test_s21_f2d_periodic) {
  float a = 1. / 3;
  s21_decimal res = {};
  char str_res[33] = "";
  char expected_lo[] = "+0.3333330000000000000000000000";
  char expected_hi[] = "+0.3333340000000000000000000000";
  ck_assert_int_eq(s21_from_float_to_decimal(a, &res), 0);
  decimal_to_string(res, str_res);
  ck_assert_str_ge(str_res, expected_lo);
  ck_assert_str_le(str_res, expected_hi);
}
END_TEST

START_TEST(test_s21_f2d_periodic_neg) {
  float a = -1. / 3;
  s21_decimal res = {};
  char str_res[33] = "";
  char expected_lo[] = "-0.3333330000000000000000000000";
  char expected_hi[] = "-0.3333340000000000000000000000";
  ck_assert_int_eq(s21_from_float_to_decimal(a, &res), 0);
  decimal_to_string(res, str_res);
  ck_assert_str_ge(str_res, expected_lo);
  ck_assert_str_le(str_res, expected_hi);
}
END_TEST

START_TEST(test_s21_f2d_small_num) {
  float a = 15e-25;
  s21_decimal res = {};
  char str_res[33] = "";
  char expected_lo[] = "+0.0000000000000000000000014999";
  char expected_hi[] = "+0.0000000000000000000000015000";
  ck_assert_int_eq(s21_from_float_to_decimal(a, &res), 0);
  decimal_to_string(res, str_res);
  ck_assert_str_ge(str_res, expected_lo);
  ck_assert_str_le(str_res, expected_hi);
}
END_TEST

START_TEST(test_s21_f2d_big_num) {
  float a = 15e25;
  s21_decimal res = {};
  char str_res[33] = "";
  char expected_lo[] = "+149999900000000000000000000.00";
  char expected_hi[] = "+150000100000000000000000000.00";
  ck_assert_int_eq(s21_from_float_to_decimal(a, &res), 0);
  decimal_to_string(res, str_res);
  ck_assert_str_ge(str_res, expected_lo);
  ck_assert_str_le(str_res, expected_hi);
}
END_TEST

START_TEST(test_s21_f2d_long_mantissa) {
  float a = 0.1234567890123456789012345678;
  s21_decimal res = {};
  char str_res[33] = "";
  char expected_lo[] = "+0.1234567890000000000000000000";
  char expected_hi[] = "+0.1234567999999999999999999999";
  ck_assert_int_eq(s21_from_float_to_decimal(a, &res), 0);
  decimal_to_string(res, str_res);
  ck_assert_str_ge(str_res, expected_lo);
  ck_assert_str_le(str_res, expected_hi);
}
END_TEST

START_TEST(test_s21_f2d_inf) {
  float a = 15e30;
  s21_decimal res = {};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &res), 1);
}
END_TEST

TCase *tc_s21_from_float() {
  TCase *tc = tcase_create("s21_from_float_to_decimal");
  tcase_add_test(tc, test_s21_f2d_periodic);
  tcase_add_test(tc, test_s21_f2d_periodic_neg);
  tcase_add_test(tc, test_s21_f2d_small_num);
  tcase_add_test(tc, test_s21_f2d_big_num);
  tcase_add_test(tc, test_s21_f2d_inf);
  tcase_add_test(tc, test_s21_f2d_long_mantissa);
  return tc;
}