#include "../s21_matrix.h"
#include "test.h"

// Positive tests

START_TEST(test_simple_sum) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2, 3}, (double[]){4, 5, 6},
                                       (double[]){7, 8, 9}},
                .rows = 3,
                .columns = 3};
  matrix_t b = a;
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){2, 4, 6}, (double[]){8, 10, 12},
                             (double[]){14, 16, 18}},
      .rows = 3,
      .columns = 3};
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_zero_sum) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2, 3}, (double[]){4, 5, 6},
                                       (double[]){7, 8, 9}},
                .rows = 3,
                .columns = 3};
  matrix_t b = {.matrix = (double *[]){(double[]){0, 0, 0}, (double[]){0, 0, 0},
                                       (double[]){0, 0, 0}},
                .rows = 3,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &a), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_complex_sum) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1, 0.2}, (double[]){0.3, 0.4}},
      .rows = 2,
      .columns = 2};
  matrix_t b = {
      .matrix = (double *[]){(double[]){0.05, 0.1}, (double[]){0.1, 156}},
      .rows = 2,
      .columns = 2};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){0.15, 0.3}, (double[]){0.4, 156.4}},
      .rows = 2,
      .columns = 2};
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_diff_dim_sum) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t b = {.matrix = (double *[]){(double[]){5e-7}, (double[]){8e-7}},
                .rows = 2,
                .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){0.1234572}, (double[]){0.7654329}},
      .rows = 2,
      .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_big_radix_diff_sum) {
  matrix_t a = {.matrix = (double *[]){(double[]){1234567e100, 7654321e79}},
                .rows = 1,
                .columns = 2};
  matrix_t b = {
      .matrix = (double *[]){(double[]){5e-7, 8e-7}}, .rows = 1, .columns = 2};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){1234567e100 + 5e-7, 7654321e79 + 8e-7}},
      .rows = 1,
      .columns = 2};
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

// Incorrect inputs

START_TEST(test_null_arg) {
  matrix_t elem = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&elem, NULL, &result), ERROR);
  ck_assert_int_eq(s21_sum_matrix(NULL, &elem, &result), ERROR);
  ck_assert_int_eq(s21_sum_matrix(&elem, &elem, NULL), ERROR);
}
END_TEST

START_TEST(test_null_matrix) {
  matrix_t elem = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t null_elem = {.matrix = NULL, .rows = 2, .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&elem, &null_elem, &result), ERROR);
  ck_assert_int_eq(s21_sum_matrix(&null_elem, &elem, &result), ERROR);
}
END_TEST

START_TEST(test_null_row) {
  matrix_t elem = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t elem_null_row = {.matrix = (double *[]){(double[]){0.1234567}, NULL},
                            .rows = 2,
                            .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&elem, &elem_null_row, &result), ERROR);
  ck_assert_int_eq(s21_sum_matrix(&elem_null_row, &elem, &result), ERROR);
}
END_TEST

// Matrix mismatch

START_TEST(test_input_matrix_mismatch) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t b = {
      .matrix = (double *[]){(double[]){0.1234567}}, .rows = 1, .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), CALC_ERR);
}
END_TEST

Suite *s21_sum_matrix_suite() {
  Suite *s = suite_create("s21_sum_matrix");

  TCase *positive_case = tcase_create("positive case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_simple_sum);
  tcase_add_test(positive_case, test_zero_sum);
  tcase_add_test(positive_case, test_complex_sum);
  tcase_add_test(positive_case, test_diff_dim_sum);
  tcase_add_test(positive_case, test_big_radix_diff_sum);

  TCase *incorrect_case = tcase_create("incorrect case");
  suite_add_tcase(s, incorrect_case);
  tcase_add_test(incorrect_case, test_null_arg);
  tcase_add_test(incorrect_case, test_null_matrix);
  tcase_add_test(incorrect_case, test_null_row);

  TCase *matrix_mismatch = tcase_create("matrix mismatch");
  suite_add_tcase(s, matrix_mismatch);
  tcase_add_test(matrix_mismatch, test_input_matrix_mismatch);

  return s;
}
