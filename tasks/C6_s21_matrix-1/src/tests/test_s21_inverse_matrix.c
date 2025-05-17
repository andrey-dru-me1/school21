#include "../s21_matrix.h"
#include "./test.h"

START_TEST(test_one_dim_matrix) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){15.16}}, .rows = 1, .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){1. / 15.16}}, .rows = 1, .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(&expected, &result), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_two_dim_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){11.12, 13.14},
                                       (double[]){15.16, 17.18}},
                .rows = 2,
                .columns = 2};
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){-2.1051858, 1.6101363},
                             (double[]){1.8576610, -1.3626115}},
      .rows = 2,
      .columns = 2};
  ck_assert_int_eq(s21_eq_matrix(&expected, &result), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_three_dim_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){11.12, 13.14, 15.16},
                                       (double[]){18.17, 20.19, 21.22},
                                       (double[]){3.21, 1.32, 2.13}},
                .rows = 3,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){-0.2283047, 0.1214586, 0.4149052},
                             (double[]){-0.4478621, 0.3803176, -0.6012910},
                             (double[]){0.6216132, -0.4187330, 0.2168349}},
      .rows = 3,
      .columns = 3};
  ck_assert_int_eq(s21_eq_matrix(&expected, &result), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

// incorrect inputs

START_TEST(test_null_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){11.12, 13.14, 15.16},
                                       (double[]){17.18, 19.20, 21.22},
                                       (double[]){23.24, 0.26, 27.28}},
                .rows = 3,
                .columns = 3};
  ck_assert_int_eq(s21_inverse_matrix(&a, NULL), ERROR);
  matrix_t res;
  ck_assert_int_eq(s21_inverse_matrix(NULL, &res), ERROR);
}
END_TEST

START_TEST(test_null_matrix_value) {
  matrix_t res;
  matrix_t a_null = {.matrix = NULL, .rows = 3, .columns = 3};
  ck_assert_int_eq(s21_inverse_matrix(&a_null, &res), ERROR);
}
END_TEST

START_TEST(test_null_matrix_row) {
  matrix_t res;
  matrix_t a_null = {
      .matrix = (double *[]){(double[]){11.12, 13.14, 15.16}, NULL,
                             (double[]){23.24, 0.26, 27.28}},
      .rows = 3,
      .columns = 3};
  ck_assert_int_eq(s21_inverse_matrix(&a_null, &res), ERROR);
}
END_TEST

START_TEST(test_zero_dim) {
  matrix_t a = {.matrix = (double *[]){(double[]){}, (double[]){}},
                .rows = 2,
                .columns = 0};
  matrix_t res;
  ck_assert_int_eq(s21_inverse_matrix(&a, &res), ERROR);
}
END_TEST

START_TEST(test_negative_dim) {
  matrix_t a = {.matrix = (double *[]){(double[]){}, (double[]){}},
                .rows = -2,
                .columns = 2};
  matrix_t res;
  ck_assert_int_eq(s21_inverse_matrix(&a, &res), ERROR);
}
END_TEST

// illegal matrix

START_TEST(test_non_square_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){11.12, 13.14, 15.16},
                                       (double[]){23.24, 0.26, 27.28}},
                .rows = 2,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), CALC_ERR);
}
END_TEST

Suite *s21_inverse_matrix_suite() {
  Suite *s = suite_create("s21_inverse_matrix");

  TCase *positive_case = tcase_create("positive_case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_one_dim_matrix);
  tcase_add_test(positive_case, test_two_dim_matrix);
  tcase_add_test(positive_case, test_three_dim_matrix);

  TCase *incorrect_inputs_tc = tcase_create("incorrect_inputs");
  suite_add_tcase(s, incorrect_inputs_tc);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_value);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_row);
  tcase_add_test(incorrect_inputs_tc, test_zero_dim);
  tcase_add_test(incorrect_inputs_tc, test_negative_dim);

  TCase *illegal_matrix_tc = tcase_create("illegal_matrix");
  suite_add_tcase(s, illegal_matrix_tc);
  tcase_add_test(illegal_matrix_tc, test_non_square_matrix);

  return s;
}
