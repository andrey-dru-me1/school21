#include <limits.h>

#include "../../s21_decimal.h"
#include "test_convert.h"

#define OK 0
#define CONVERTATION_ERR 1

START_TEST(test_s21_to_int_0) {
  s21_decimal src = {{0, 0, 0, 0}};
  int dst;
  int expected = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK);
  ck_assert_int_eq(expected, dst);
}
END_TEST

START_TEST(test_s21_to_int_1) {
  s21_decimal src = {{INT_MAX, 0, 0, 0}};
  int dst;
  int expected = INT_MAX;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK);
  ck_assert_int_eq(expected, dst);
}
END_TEST

START_TEST(test_s21_to_int_neg) {
  s21_decimal src = {{456, 0, 0, 1u << 31}};
  int dst;
  int expected = -456;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK);
  ck_assert_int_eq(expected, dst);
}
END_TEST

START_TEST(test_s21_to_int_fraction) {
  s21_decimal src = {{3456, 0, 0, 2 << 16}};
  int dst;
  int expected = 34;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK);
  ck_assert_int_eq(expected, dst);
}
END_TEST

START_TEST(test_s21_to_int_2) {
  s21_decimal src = {{UINT_MAX, UINT_MAX, 0, 0}};
  int dst;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CONVERTATION_ERR);
}
END_TEST

START_TEST(test_s21_to_int_3) {
  s21_decimal src = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, NULL), CONVERTATION_ERR);
}
END_TEST

TCase *tc_s21_to_int() {
  TCase *tc = tcase_create("s21_to_int");
  tcase_add_test(tc, test_s21_to_int_0);
  tcase_add_test(tc, test_s21_to_int_1);
  tcase_add_test(tc, test_s21_to_int_2);
  tcase_add_test(tc, test_s21_to_int_3);
  tcase_add_test(tc, test_s21_to_int_neg);
  tcase_add_test(tc, test_s21_to_int_fraction);
  return tc;
}