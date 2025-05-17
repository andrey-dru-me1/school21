#include "../../s21_decimal.h"
#include "../string_converter/string_converter.h"
#include "test_arithm.h"

START_TEST(test_s21_add_ordinary_positive) {
  s21_decimal a = {{1000000000, 65, 45, 0}};
  s21_decimal b = {{223, 67, 4, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0x3b9acadf, 0x00000084, 0x31, 0}};
  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_ordinary_negative) {
  s21_decimal a = {{1000000000, 65, 45, (1u << 31) | (1 << 16)}};
  s21_decimal b = {{223, 67, 4, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {
      {0x3b9ac14a, 0xfffffda3, 0x4, (1u << 31) | (1 << 16)}};
  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_big_numbers) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, (15 << 16)}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, (1 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  char expected[] = "+07922816251426512987516909298.";
  ck_assert_int_eq(s21_add(a, b, &res), 0);
  char str_res[33];
  decimal_to_string(res, str_res);
  ck_assert_str_eq(expected, str_res);
}
END_TEST

START_TEST(test_s21_add_positive_INF) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal b = {{223, 67, 4, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &res), 1);
}
END_TEST

START_TEST(test_s21_add_negative_INF) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 1u << 31}};
  s21_decimal b = {{223, 67, 4, 1u << 31}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &res), 2);
}
END_TEST

START_TEST(test_s21_add_negative_reverse) {
  s21_decimal a = {{223, 67, 4, 0}};
  s21_decimal b = {{1000000000, 65, 45, (1u << 31) | (1 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {
      {0x3b9ac14a, 0xfffffda3, 0x4, (1u << 31) | (1 << 16)}};
  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_large_nums) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 5 << 16}};
  s21_decimal b = {{223, 67, 4, 5 << 16}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0xb3333349, 6, 0x1999999a, 4 << 16}};
  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

TCase *tc_s21_add() {
  TCase *tc = tcase_create("s21_add");
  tcase_add_test(tc, test_s21_add_ordinary_positive);
  tcase_add_test(tc, test_s21_add_ordinary_negative);
  tcase_add_test(tc, test_s21_add_big_numbers);
  tcase_add_test(tc, test_s21_add_positive_INF);
  tcase_add_test(tc, test_s21_add_negative_INF);
  tcase_add_test(tc, test_s21_add_large_nums);
  tcase_add_test(tc, test_s21_add_negative_reverse);
  return tc;
}
