#include "test.h"

#include <check.h>
#include <stdlib.h>

int main(void) {
  Suite *s = s21_decimal_arithm_suite();
  SRunner *sr = srunner_create(s);

  srunner_add_suite(sr, s21_decimal_another_foos_suite());
  srunner_add_suite(sr, s21_decimal_converters_parsers_suite());
  srunner_add_suite(sr, s21_decimal_comp_op_suite());

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}