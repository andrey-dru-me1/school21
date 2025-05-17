#include "../../s21_decimal.h"
#include "../string_converter/string_converter.h"
#include "../test.h"
#include "test_convert.h"

Suite *s21_decimal_converters_parsers_suite() {
  Suite *s = suite_create("s21_decimal_converters_parsers");
  suite_add_tcase(s, tc_s21_from_int());
  suite_add_tcase(s, tc_s21_from_float());
  suite_add_tcase(s, tc_s21_to_int());
  suite_add_tcase(s, tc_s21_to_float());
  return s;
}
