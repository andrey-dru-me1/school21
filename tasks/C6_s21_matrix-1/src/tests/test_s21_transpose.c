#include "../s21_matrix.h"
#include "./test.h"

// positive case

START_TEST(test_one_dim_matrix) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){15.16}}, .rows = 1, .columns = 1};
  matrix_t res;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &res), 1);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_square_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){1.23, 4.56, 7.89},
                                       (double[]){9.87, 6.54, 3.21},
                                       (double[]){1.11, 4.44, 7.77}},
                .rows = 3,
                .columns = 3};
  matrix_t expected = {.matrix = (double *[]){(double[]){1.23, 9.87, 1.11},
                                              (double[]){4.56, 6.54, 4.44},
                                              (double[]){7.89, 3.21, 7.77}},
                       .rows = 3,
                       .columns = 3};
  matrix_t res;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_symm_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){1.23, 4.56, 7.89},
                                       (double[]){4.56, 6.54, 3.21},
                                       (double[]){7.89, 3.21, 7.77}},
                .rows = 3,
                .columns = 3};
  matrix_t res;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &res), 1);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_zero_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){0, 0, 0}, (double[]){0, 0, 0},
                                       (double[]){0, 0, 0}},
                .rows = 3,
                .columns = 3};
  matrix_t res;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &res), 1);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_rect_matrix) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){1.23, 4.56}, (double[]){9.87, 6.54},
                             (double[]){1.11, 4.44}},
      .rows = 3,
      .columns = 2};
  matrix_t expected = {.matrix = (double *[]){(double[]){1.23, 9.87, 1.11},
                                              (double[]){4.56, 6.54, 4.44}},
                       .rows = 2,
                       .columns = 3};
  matrix_t res;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&res);
}
END_TEST

// incorrect inputs

START_TEST(test_null_arg) {
  matrix_t elem = {
      .matrix = (double *[]){(double[]){15.16}}, .rows = 1, .columns = 1};
  ck_assert_int_eq(s21_transpose(NULL, &elem), 1);
  ck_assert_int_eq(s21_transpose(&elem, NULL), 1);
  ck_assert_int_eq(s21_transpose(NULL, NULL), 1);
}

START_TEST(test_null_matrix_value) {
  matrix_t res;
  matrix_t a = {.matrix = NULL, .rows = 1, .columns = 1};
  ck_assert_int_eq(s21_transpose(&a, &res), 1);
}

START_TEST(test_null_matrix_row) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){15.16}, NULL, (double[]){19.20}},
      .rows = 3,
      .columns = 1};
  matrix_t res;
  ck_assert_int_eq(s21_transpose(&a, &res), 1);
}

START_TEST(test_zero_rows_columns) {
  matrix_t elem1 = {
      .matrix = (double *[]){(double[]){}, (double[]){}, (double[]){}},
      .rows = 3,
      .columns = 0};
  matrix_t elem2 = {.matrix = (double *[]){}, .rows = 0, .columns = 3};
  ck_assert_int_eq(s21_transpose(&elem1, &elem2), 1);
  ck_assert_int_eq(s21_transpose(&elem2, &elem1), 1);
}

Suite *s21_transpose_suite() {
  Suite *s = suite_create("s21_transpose");

  TCase *positive_case = tcase_create("positive_case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_one_dim_matrix);
  tcase_add_test(positive_case, test_square_matrix);
  tcase_add_test(positive_case, test_zero_matrix);
  tcase_add_test(positive_case, test_symm_matrix);
  tcase_add_test(positive_case, test_rect_matrix);

  TCase *incorrect_inputs_tc = tcase_create("incorrect_inputs");
  suite_add_tcase(s, incorrect_inputs_tc);
  tcase_add_test(incorrect_inputs_tc, test_null_arg);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_value);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_row);
  tcase_add_test(incorrect_inputs_tc, test_zero_rows_columns);

  return s;
}