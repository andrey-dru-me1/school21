#include <check.h>

#include "../s21_decimal.h"
#include "string_converter/string_converter.h"
#include "test.h"

START_TEST(test_s21_floor) {
  s21_decimal a = {{10, 65, 45, (4 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  char expected[] = "+00000000000083010348359610269.";
  ck_assert_int_eq(s21_floor(a, &res), 0);
  char str_res[33];
  decimal_to_string(res, str_res);
  ck_assert_str_eq(expected, str_res);
}
END_TEST

START_TEST(test_s21_floor_neg) {
  s21_decimal a = {{10, 65, 45, (1u << 31) | (4 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  char expected[] = "-00000000000083010348359610270.";
  ck_assert_int_eq(s21_floor(a, &res), 0);

  char str_res[33];
  decimal_to_string(res, str_res);
  ck_assert_str_eq(expected, str_res);
}
END_TEST

START_TEST(test_s21_round) {
  s21_decimal a = {{10, 65, 45, (4 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  char expected[] = "+00000000000083010348359610270.";
  ck_assert_int_eq(s21_round(a, &res), 0);

  char str_res[33];
  decimal_to_string(res, str_res);
  ck_assert_str_eq(expected, str_res);
}
END_TEST

START_TEST(test_s21_truncate) {
  s21_decimal a = {{10, 65, 45, (4 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  char expected[] = "+00000000000083010348359610269.";
  ck_assert_int_eq(s21_truncate(a, &res), 0);

  char str_res[33];
  decimal_to_string(res, str_res);
  ck_assert_str_eq(expected, str_res);
}
END_TEST

START_TEST(test_s21_negate_n) {
  s21_decimal a = {{10, 65, 45, (4 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  char expected[] = "-0000000083010348359610269.6970";
  ck_assert_int_eq(s21_negate(a, &res), 0);

  char str_res[33];
  decimal_to_string(res, str_res);
  ck_assert_str_eq(expected, str_res);
}
END_TEST

START_TEST(test_s21_negate_p) {
  s21_decimal a = {{10, 65, 45, (1u << 31) | (4 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  char expected[] = "+0000000083010348359610269.6970";
  ck_assert_int_eq(s21_negate(a, &res), 0);

  char str_res[33];
  decimal_to_string(res, str_res);
  ck_assert_str_eq(expected, str_res);
}
END_TEST

Suite *s21_decimal_another_foos_suite() {
  Suite *s = suite_create("s21_decimal_another_foos");

  TCase *tc_s21_floor = tcase_create("s21_floor");
  suite_add_tcase(s, tc_s21_floor);
  tcase_add_test(tc_s21_floor, test_s21_floor);
  tcase_add_test(tc_s21_floor, test_s21_floor_neg);

  TCase *tc_s21_round = tcase_create("s21_round");
  suite_add_tcase(s, tc_s21_round);
  tcase_add_test(tc_s21_round, test_s21_round);

  TCase *tc_s21_truncate = tcase_create("s21_truncate");
  suite_add_tcase(s, tc_s21_truncate);
  tcase_add_test(tc_s21_truncate, test_s21_truncate);

  TCase *tc_s21_negate = tcase_create("s21_negate");
  suite_add_tcase(s, tc_s21_negate);
  tcase_add_test(tc_s21_negate, test_s21_negate_n);
  tcase_add_test(tc_s21_negate, test_s21_negate_p);

  return s;
}
