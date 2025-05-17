#include "../../s21_decimal.h"
#include "test_arithm.h"

START_TEST(test_s21_sub_ordinary_positive) {
  s21_decimal a = {{0x3b9acadf, 0x00000084, 0x31, 0}};
  s21_decimal b = {{223, 67, 4, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{1000000000, 65, 45, 0}};
  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_ordinary_negative) {
  s21_decimal a = {{1000000000, 65, 45, 1u << 31}};
  s21_decimal b = {{223, 67, 4, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0x3b9acadf, 0x00000084, 0x31, 1u << 31}};
  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_negative) {
  s21_decimal a = {{0x3b9acadf, 0x00000084, 0x31, 1u << 31}};
  s21_decimal b = {{223, 67, 4, 1u << 31}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{1000000000, 65, 45, 1u << 31}};
  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_negative_INF) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 1u << 31}};
  s21_decimal b = {{223, 67, 4, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(a, b, &res), 2);
}
END_TEST

START_TEST(test_s21_sub_positive_INF) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal b = {{223, 67, 4, 1u << 31}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(a, b, &res), 1);
}
END_TEST

TCase *tc_s21_sub() {
  TCase *tc = tcase_create("s21_sub");
  tcase_add_test(tc, test_s21_sub_ordinary_positive);
  tcase_add_test(tc, test_s21_sub_ordinary_negative);
  tcase_add_test(tc, test_s21_sub_negative);
  tcase_add_test(tc, test_s21_sub_negative_INF);
  tcase_add_test(tc, test_s21_sub_positive_INF);
  return tc;
}
