#include "../../s21_decimal.h"
#include "../string_converter/string_converter.h"
#include "test_arithm.h"

START_TEST(test_s21_div_ordinary) {
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char expected[] = "+2.0000000000000000000000000000";
  char test[36] = {0};
  decimal_to_string(res, test);
  ck_assert_str_eq(test, expected);
}
END_TEST

START_TEST(test_s21_div_ordinary_exp) {
  s21_decimal a = {{0, 0, 6, (1u << 31) | (7 << 16)}};
  s21_decimal b = {{0, 0, 3, (1u << 31) | (15 << 16)}};
  char expected[] = "+200000000.00000000000000000000";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_inverse_exp) {
  s21_decimal a = {{0, 0, 6, (1u << 31) | (15 << 16)}};
  s21_decimal b = {{0, 0, 3, (7 << 16)}};
  char expected[] = "-0.0000000200000000000000000000";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_periodic) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  char expected[] = "+0.3333333333333333333333333333";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_long_mantissa) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{0xffbac10e, 0xffffffff, 0xffffffff, 28 << 16}};
  char expected[] = "+0.1262177448353618888658838001";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_round_up) {
  s21_decimal a = {{411601039, 3190096481, 685266662, 28 << 16}};
  s21_decimal b = {{2, 0, 0, 0}};
  char expected[] = "+0.6320469374930293225402156104";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{132, 456, 789, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_big) {
  s21_decimal a = {{789, 456, 123, (17 << 16)}};
  s21_decimal b = {{132, 456, 789, (3 << 16)}};
  char expected[] = "+0.0000000000000015589353623526";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_one_by_big) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, (28 << 16)}};
  char expected[] = "+0.1262177448353618888658765704";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_mean) {
  s21_decimal a = {{789, 456, 0, (5 << 16)}};
  s21_decimal b = {{132, 356, 0, (3 << 16)}};
  char expected[] = "+0.0128089887680993451272585377";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_bigshort) {
  s21_decimal a = {{789, 456, 10, (1 << 16)}};
  s21_decimal b = {{132, 356, 0, (3 << 16)}};
  char expected[] = "+12064515003.452846903403781575";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_edge_case) {
  s21_decimal a = {{309237645, 2714419331, 4260607557, (26 << 16)}};
  s21_decimal b = {{992, 0, 0, (0 << 16)}};
  char expected[] = "+0.7922816251426433759354395034";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_edge_case_shift) {
  s21_decimal a = {{309237645, 2714419331, 4260607557, (20 << 16)}};
  s21_decimal b = {{992, 0, 0, (0 << 16)}};
  char expected[] = "+0792281.6251426433759354395034";
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 0);
  char result[33];
  decimal_to_string(res, result);
  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_div_edge_case_inf) {
  s21_decimal a = {{309237645, 2714419331, 4260607557, (0 << 16)}};
  s21_decimal b = {{992, 0, 0, (3 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 1);
}
END_TEST

START_TEST(test_s21_div_by_zero) {
  s21_decimal a = {{132, 456, 789, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 3);
}
END_TEST

START_TEST(test_s21_div_inf) {
  s21_decimal a = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal b = {{1, 0, 0, (28 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 1);
}
END_TEST

START_TEST(test_s21_div_neg_inf) {
  s21_decimal a = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal b = {{1, 0, 0, (1u << 31) | (28 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &res), 2);
}
END_TEST

TCase *tc_s21_div() {
  TCase *tc = tcase_create("s21_div");
  tcase_add_test(tc, test_s21_div_ordinary);
  tcase_add_test(tc, test_s21_div_ordinary_exp);
  tcase_add_test(tc, test_s21_div_inverse_exp);
  tcase_add_test(tc, test_s21_div_periodic);
  tcase_add_test(tc, test_s21_div_big);
  tcase_add_test(tc, test_s21_div_zero);
  tcase_add_test(tc, test_s21_div_by_zero);
  tcase_add_test(tc, test_s21_div_inf);
  tcase_add_test(tc, test_s21_div_neg_inf);
  tcase_add_test(tc, test_s21_div_mean);
  tcase_add_test(tc, test_s21_div_bigshort);
  tcase_add_test(tc, test_s21_div_one_by_big);
  tcase_add_test(tc, test_s21_div_edge_case);
  tcase_add_test(tc, test_s21_div_edge_case_shift);
  tcase_add_test(tc, test_s21_div_edge_case_inf);
  tcase_add_test(tc, test_s21_div_long_mantissa);
  tcase_add_test(tc, test_s21_div_round_up);
  return tc;
}
