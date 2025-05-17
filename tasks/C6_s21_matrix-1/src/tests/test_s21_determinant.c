#include "../s21_matrix.h"
#include "./test.h"

// positive case

START_TEST(test_one_dim_matrix) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){15.63}}, .rows = 1, .columns = 1};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 0);
  ck_assert_double_eq_tol(det, 15.63, 1e-7);
}
END_TEST

START_TEST(test_two_dim_matrix) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){1.15, 2.16}, (double[]){3.17, 4.18}},
      .rows = 2,
      .columns = 2};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 0);
  ck_assert_double_eq_tol(det, 1.15 * 4.18 - 2.16 * 3.17, 1e-7);
}
END_TEST

START_TEST(test_three_dim_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){1.15, 2.16, 9.654},
                                       (double[]){3.17, 4.18, 8.123},
                                       (double[]){5.578, 6.485, 3.215}},
                .rows = 3,
                .columns = 3};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 0);
  ck_assert_double_eq_tol(det, 4.0998289, 1e-7);
}
END_TEST

START_TEST(test_id_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 0, 0, 0, 0, 0},
                                       (double[]){0, 1, 0, 0, 0, 0},
                                       (double[]){0, 0, 1, 0, 0, 0},
                                       (double[]){0, 0, 0, 1, 0, 0},
                                       (double[]){0, 0, 0, 0, 1, 0},
                                       (double[]){0, 0, 0, 0, 0, 1}},
                .rows = 6,
                .columns = 6};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 0);
  ck_assert_double_eq_tol(det, 1, 1e-7);
}
END_TEST

START_TEST(test_zero_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){0, 0, 0, 0, 0, 0},
                                       (double[]){0, 0, 0, 0, 0, 0},
                                       (double[]){0, 0, 0, 0, 0, 0},
                                       (double[]){0, 0, 0, 0, 0, 0},
                                       (double[]){0, 0, 0, 0, 0, 0},
                                       (double[]){0, 0, 0, 0, 0, 0}},
                .rows = 6,
                .columns = 6};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 0);
  ck_assert_double_eq_tol(det, 0, 1e-7);
}
END_TEST

// incorrect inputs

START_TEST(test_null_matrix) {
  double det;
  ck_assert_int_eq(s21_determinant(NULL, &det), 1);
}
END_TEST

START_TEST(test_null_double) {
  matrix_t a = {.matrix = (double *[]){(double[]){1.15, 2.16, 9.654},
                                       (double[]){3.17, 4.18, 8.123},
                                       (double[]){5.578, 6.485, 3.215}},
                .rows = 3,
                .columns = 3};
  ck_assert_int_eq(s21_determinant(&a, NULL), 1);
}
END_TEST

START_TEST(test_null_matrix_val) {
  matrix_t a = {.matrix = NULL, .rows = 3, .columns = 3};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 1);
}
END_TEST

START_TEST(test_null_matrix_row) {
  matrix_t a = {.matrix = (double *[]){(double[]){1.15, 2.16, 9.654}, NULL,
                                       (double[]){5.578, 6.485, 3.215}},
                .rows = 3,
                .columns = 3};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 1);
}
END_TEST

START_TEST(test_zero_dim_matrix) {
  matrix_t a = {.matrix = (double *[]){}, .rows = 0, .columns = 0};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 1);
}
END_TEST

// illegal matrix

START_TEST(test_non_square_matrix) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){1, 2}}, .rows = 1, .columns = 2};
  double det;
  ck_assert_int_eq(s21_determinant(&a, &det), 2);
}
END_TEST

Suite *s21_determinant_suite() {
  Suite *s = suite_create("s21_determinant");

  TCase *positive_case = tcase_create("positive_case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_one_dim_matrix);
  tcase_add_test(positive_case, test_two_dim_matrix);
  tcase_add_test(positive_case, test_three_dim_matrix);
  tcase_add_test(positive_case, test_id_matrix);
  tcase_add_test(positive_case, test_zero_matrix);

  TCase *incorrect_inputs_tc = tcase_create("incorrect_inputs");
  suite_add_tcase(s, incorrect_inputs_tc);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix);
  tcase_add_test(incorrect_inputs_tc, test_null_double);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_val);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_row);
  tcase_add_test(incorrect_inputs_tc, test_zero_dim_matrix);

  TCase *illegal_matrix_tc = tcase_create("illegal_matrix");
  suite_add_tcase(s, illegal_matrix_tc);
  tcase_add_test(illegal_matrix_tc, test_non_square_matrix);

  return s;
}
