#include "../../s21_decimal.h"
#include "test_arithm.h"

START_TEST(test_s21_mul_nooverflow) {
  s21_decimal a = {{50, 2, 0, 0}};
  s21_decimal b = {{223, 67, 0, 0}};
  s21_decimal expected = {{0x00002b8e, 0x00000ed4, 0x86, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_nooverflow_sign) {
  s21_decimal a = {{50, 2, 0, 1u << 31}};
  s21_decimal b = {{223, 67, 0, 0}};
  s21_decimal expected = {{0x00002b8e, 0x00000ed4, 0x86, 1u << 31}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_nooverflow_2sign) {
  s21_decimal a = {{50, 2, 0, 1u << 31}};
  s21_decimal b = {{223, 67, 0, 1u << 31}};
  s21_decimal expected = {{0x00002b8e, 0x00000ed4, 0x86, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_nooverflow_exp) {
  s21_decimal a = {{50, 2, 0, (3 << 16) | (1u << 31)}};
  s21_decimal b = {{223, 67, 0, (2 << 16) | (1u << 31)}};
  s21_decimal expected = {{0x00002b8e, 0x00000ed4, 0x86, (5 << 16)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_overflow) {
  s21_decimal a = {
      {0xffffffff, 0xffffffff, 0x0000ffff, (27 << 16) | (1u << 31)}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0x0000ffff, (28 << 16)}};
  s21_decimal expected = {
      {0xf03f243c, 0x3a68dbc8, 0x4f, (28 << 16) | (1u << 31)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_overflow_zero) {
  s21_decimal a = {{0xffffffff, 0, 0, (27 << 16) | (1u << 31)}};
  s21_decimal b = {{0xffffffff, 0, 0, (28 << 16)}};
  s21_decimal expected = {{0, 0, 0, (28 << 16) | (1u << 31)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_INF) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, (1u << 31)}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, (1u << 31)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 1);
}
END_TEST

START_TEST(test_s21_mul_NEG_INF) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, (1u << 31)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(a, b, &res), 2);
}
END_TEST

TCase *tc_s21_mul() {
  TCase *tc = tcase_create("s21_mul");
  tcase_add_test(tc, test_s21_mul_nooverflow);
  tcase_add_test(tc, test_s21_mul_nooverflow_sign);
  tcase_add_test(tc, test_s21_mul_nooverflow_2sign);
  tcase_add_test(tc, test_s21_mul_nooverflow_exp);
  tcase_add_test(tc, test_s21_mul_overflow);
  tcase_add_test(tc, test_s21_mul_INF);
  tcase_add_test(tc, test_s21_mul_NEG_INF);
  tcase_add_test(tc, test_s21_mul_overflow_zero);
  return tc;
}
