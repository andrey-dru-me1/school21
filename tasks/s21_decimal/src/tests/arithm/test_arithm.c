#include "test_arithm.h"

#include <check.h>

#include "../test.h"

Suite *s21_decimal_arithm_suite() {
  Suite *s = suite_create("s21_decimal_arithm");
  suite_add_tcase(s, tc_s21_add());
  suite_add_tcase(s, tc_s21_sub());
  suite_add_tcase(s, tc_s21_mul());
  suite_add_tcase(s, tc_s21_div());
  return s;
}
