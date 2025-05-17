#include <check.h>

#include "../main/utils/utils.h"
#include "test.h"

START_TEST(test_get_exp) {
  s21_decimal number = {.bits = {159, 0, 0, 0x7fff0dff}};
  ck_assert_uint_eq(get_exp(&number), 13);
  number.bits[3] = (28 << 8) | (1u << 31);
  ck_assert_uint_eq(get_exp(&number), 28);
  number.bits[3] = 0xffffffff ^ (0xff << 8);
  ck_assert_uint_eq(get_exp(&number), 0);
}
END_TEST

START_TEST(test_get_sign) {
  s21_decimal number = {.bits = {159, 0, 0, 0x7fff0dff}};
  ck_assert_uint_eq(get_sign(&number), 0);
  number.bits[3] = 0xffff0dff;
  ck_assert_uint_eq(get_sign(&number), 1);
  number.bits[3] = 0xb3000d00;
  ck_assert_uint_eq(get_sign(&number), 1);
}
END_TEST

START_TEST(test_set_exp) {
  s21_decimal number = {.bits = {159, 0, 0, 0x7fff0dff}};
  ck_assert_uint_eq(set_exp(&number, 28), 0);
  ck_assert_uint_eq(get_exp(&number), 28);
  ck_assert_uint_eq(set_exp(&number, 8), 0);
  ck_assert_uint_eq(get_exp(&number), 8);
  ck_assert_uint_eq(set_exp(&number, 0), 0);
  ck_assert_uint_eq(get_exp(&number), 0);
  ck_assert_uint_eq(set_exp(&number, 29), -1);
  ck_assert_uint_eq(set_exp(&number, -89), -1);
}
END_TEST

START_TEST(test_set_sign) {
  s21_decimal number = {.bits = {159, 0, 0, 0x7fff0dff}};
  ck_assert_uint_eq(set_sign(&number, 1), 0);
  ck_assert_uint_eq(get_sign(&number), 1);
  ck_assert_uint_eq(set_sign(&number, 0), 0);
  ck_assert_uint_eq(get_sign(&number), 0);
  ck_assert_uint_eq(set_sign(&number, 2), -1);
  ck_assert_uint_eq(set_sign(&number, -1), -1);
  ck_assert_uint_eq(set_sign(&number, -89), -1);
}
END_TEST

Suite *s21_decimal_utils_suite(void) {
  Suite *s = suite_create("s21_decimal_utils");

  TCase *tc_get_exp = tcase_create("get_exp");
  tcase_add_test(tc_get_exp, test_get_exp);
  suite_add_tcase(s, tc_get_exp);

  TCase *tc_get_sign = tcase_create("get_sign");
  tcase_add_test(tc_get_exp, test_get_sign);
  suite_add_tcase(s, tc_get_sign);

  TCase *tc_set_exp = tcase_create("set_exp");
  tcase_add_test(tc_get_exp, test_set_exp);
  suite_add_tcase(s, tc_set_exp);

  TCase *tc_set_sign = tcase_create("set_sign");
  tcase_add_test(tc_get_exp, test_set_sign);
  suite_add_tcase(s, tc_set_sign);

  return s;
}
