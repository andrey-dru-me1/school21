#include "../s21_matrix.h"
#include "test.h"

// Positive tests

START_TEST(test_simple_mult_number) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2, 3}, (double[]){4, 5, 6},
                                       (double[]){7, 8, 9}},
                .rows = 3,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_mult_number(&a, 2.3, &result), OK);
  matrix_t expected = {.matrix = (double *[]){(double[]){2.3, 4.6, 6.9},
                                              (double[]){9.2, 11.5, 13.8},
                                              (double[]){16.1, 18.4, 20.7}},
                       .rows = 3,
                       .columns = 3};
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_one) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2, 3}, (double[]){4, 5, 6},
                                       (double[]){7, 8, 9}},
                .rows = 3,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_mult_number(&a, 1, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &a), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_zero) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2, 3}, (double[]){4, 5, 6},
                                       (double[]){7, 8, 9}},
                .rows = 3,
                .columns = 3};
  matrix_t result;
  matrix_t expected = {
      .matrix = (double *[]){(double[]){0, 0, 0}, (double[]){0, 0, 0},
                             (double[]){0, 0, 0}},
      .rows = 3,
      .columns = 3};
  ck_assert_int_eq(s21_mult_number(&a, 0, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

// Incorrect inputs

START_TEST(test_null_arg) {
  matrix_t result;
  ck_assert_int_eq(s21_mult_number(NULL, 15, &result), ERROR);
}
END_TEST

START_TEST(test_null_matrix) {
  matrix_t elem = {.matrix = NULL, .rows = 2, .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_mult_number(&elem, 15, &result), ERROR);
}
END_TEST

START_TEST(test_null_row) {
  matrix_t elem = {.matrix = (double *[]){(double[]){0.1234567}, NULL},
                   .rows = 2,
                   .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_mult_number(&elem, 15, &result), ERROR);
}
END_TEST

Suite *s21_mult_number_suite() {
  Suite *s = suite_create("s21_mult_number");

  TCase *positive_case = tcase_create("positive case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_simple_mult_number);
  tcase_add_test(positive_case, test_mult_one);
  tcase_add_test(positive_case, test_mult_zero);

  TCase *incorrect_case = tcase_create("incorrect case");
  suite_add_tcase(s, incorrect_case);
  tcase_add_test(incorrect_case, test_null_arg);
  tcase_add_test(incorrect_case, test_null_matrix);
  tcase_add_test(incorrect_case, test_null_row);

  return s;
}
