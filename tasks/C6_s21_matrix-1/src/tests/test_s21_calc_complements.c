#include "../s21_matrix.h"
#include "./test.h"

// positive case

START_TEST(test_one_dim_matrix) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){15.16}}, .rows = 1, .columns = 1};
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(&a, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){1.}}, .rows = 1, .columns = 1};
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
  ck_assert_int_eq(s21_calc_complements(&a, &result), OK);
  matrix_t expected = {.matrix = (double *[]){(double[]){17.18, -15.16},
                                              (double[]){-13.14, 11.12}},
                       .rows = 2,
                       .columns = 2};
  ck_assert_int_eq(s21_eq_matrix(&expected, &result), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_three_dim_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){11.12, 13.14, 15.16},
                                       (double[]){17.18, 19.20, 21.22},
                                       (double[]){23.24, 25.26, 27.28}},
                .rows = 3,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(&a, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){-12.2412, 24.4824, -12.2412},
                             (double[]){24.4824, -48.9648, 24.4824},
                             (double[]){-12.2412, 24.4824, -12.2412}},
      .rows = 3,
      .columns = 3};
  ck_assert_int_eq(s21_eq_matrix(&expected, &result), SUCCESS);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_three_dim_matrix_assym) {
  matrix_t a = {.matrix = (double *[]){(double[]){11.12, 13.14, 15.16},
                                       (double[]){17.18, 19.20, 21.22},
                                       (double[]){23.24, 0.26, 27.28}},
                .rows = 3,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(&a, &result), OK);
  matrix_t expected = {
      .matrix = (double *[]){(double[]){518.2588, 24.4824, -441.7412},
                             (double[]){-354.5176, -48.9648, 302.4824},
                             (double[]){-12.2412, 24.4824, -12.2412}},
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
  ck_assert_int_eq(s21_calc_complements(&a, NULL), ERROR);
  ck_assert_int_eq(s21_calc_complements(NULL, &a), ERROR);
}
END_TEST

START_TEST(test_null_matrix_value) {
  matrix_t a_null = {.matrix = NULL, .rows = 3, .columns = 3};
  matrix_t res;
  ck_assert_int_eq(s21_calc_complements(&a_null, &res), ERROR);
}
END_TEST

START_TEST(test_null_matrix_row) {
  matrix_t res;
  matrix_t a_null = {
      .matrix = (double *[]){(double[]){11.12, 13.14, 15.16}, NULL,
                             (double[]){23.24, 0.26, 27.28}},
      .rows = 3,
      .columns = 3};
  ck_assert_int_eq(s21_calc_complements(&a_null, &res), ERROR);
}
END_TEST

START_TEST(test_zero_dim) {
  matrix_t a = {.matrix = (double *[]){(double[]){}, (double[]){}},
                .rows = 2,
                .columns = 0};
  ck_assert_int_eq(s21_calc_complements(&a, &a), ERROR);
  ck_assert_int_eq(s21_calc_complements(&a, &a), ERROR);
}
END_TEST

START_TEST(test_negative_dim) {
  matrix_t a = {.matrix = (double *[]){(double[]){}, (double[]){}},
                .rows = -2,
                .columns = 2};
  ck_assert_int_eq(s21_calc_complements(&a, &a), ERROR);
  ck_assert_int_eq(s21_calc_complements(&a, &a), ERROR);
}
END_TEST

// Illegal matrix

START_TEST(test_non_square_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){11.12, 13.14, 15.16},
                                       (double[]){23.24, 0.26, 27.28}},
                .rows = 2,
                .columns = 3};
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(&a, &result), CALC_ERR);
}
END_TEST

Suite *s21_calc_complements_suite() {
  Suite *s = suite_create("s21_calc_complements");

  TCase *positive_case = tcase_create("positive_case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_one_dim_matrix);
  tcase_add_test(positive_case, test_two_dim_matrix);
  tcase_add_test(positive_case, test_three_dim_matrix);
  tcase_add_test(positive_case, test_three_dim_matrix_assym);

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
