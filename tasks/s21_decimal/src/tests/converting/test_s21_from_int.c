#include <limits.h>

#include "../../s21_decimal.h"
#include "test_convert.h"

#define OK 0
#define CONVERTATION_ERR 1

START_TEST(test_s21_from_int_0) {
  int src = 0;
  s21_decimal dst = {};
  s21_decimal expected = {};
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), OK);
  ck_assert_mem_eq(&dst, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_from_int_1) {
  int src = INT_MAX;
  s21_decimal dst = {};
  s21_decimal expected = {{0x7fffffff, 0, 0, 0}};
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), OK);
  ck_assert_mem_eq(&dst, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_from_int_2) {
  int src = -INT_MAX - 1;
  s21_decimal dst = {};
  s21_decimal expected = {{0x80000000, 0, 0, (1u << 31)}};
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), OK);
  ck_assert_mem_eq(&dst, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_from_int_ordinary) {
  int src = 23;
  s21_decimal dst = {};
  s21_decimal expected = {{23, 0, 0, 0}};
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), OK);
  ck_assert_mem_eq(&dst, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_from_int_ordinary_neg) {
  int src = -23;
  s21_decimal dst = {};
  s21_decimal expected = {{23, 0, 0, 1u << 31}};
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), OK);
  ck_assert_mem_eq(&dst, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_from_int_3) {
  ck_assert_int_eq(s21_from_int_to_decimal(0, NULL), CONVERTATION_ERR);
}
END_TEST

TCase *tc_s21_from_int() {
  TCase *tc = tcase_create("s21_from_int");
  tcase_add_test(tc, test_s21_from_int_0);
  tcase_add_test(tc, test_s21_from_int_1);
  tcase_add_test(tc, test_s21_from_int_2);
  tcase_add_test(tc, test_s21_from_int_3);
  tcase_add_test(tc, test_s21_from_int_ordinary);
  tcase_add_test(tc, test_s21_from_int_ordinary_neg);
  return tc;
}