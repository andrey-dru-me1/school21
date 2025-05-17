#include "../s21_matrix.h"
#include "./test.h"

// positive_case

START_TEST(test_one_dim_matrices) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){15.16}}, .rows = 1, .columns = 1};
  matrix_t b = {
      .matrix = (double *[]){(double[]){17.18}}, .rows = 1, .columns = 1};
  matrix_t expected = {.matrix = (double *[]){(double[]){15.16 * 17.18}},
                       .rows = 1,
                       .columns = 1};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&res);
}

START_TEST(test_two_dim_matrices) {
  matrix_t a = {.matrix = (double *[]){(double[]){15.16, 17.18},
                                       (double[]){19.20, 20.21}},
                .rows = 2,
                .columns = 2};
  matrix_t b = {.matrix = (double *[]){(double[]){21.22, 23.24},
                                       (double[]){25.26, 27.28}},
                .rows = 2,
                .columns = 2};
  matrix_t expected = {
      .matrix = (double *[]){(double[]){15.16 * 21.22 + 17.18 * 25.26,
                                        15.16 * 23.24 + 17.18 * 27.28},
                             (double[]){19.20 * 21.22 + 20.21 * 25.26,
                                        19.20 * 23.24 + 20.21 * 27.28}},
      .rows = 2,
      .columns = 2};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&res);
}

START_TEST(test_six_dim_matrices) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2, 3, 4, 5, 6},
                                       (double[]){6, 8, 7, 2, 3, 4},
                                       (double[]){1.1, 2.2, 7.7, 8.8, 9.9, 4.4},
                                       (double[]){1.2, 3.4, 5.6, 7.8, 9.1, 4.5},
                                       (double[]){5, 6, 7, 5, 6, 7},
                                       (double[]){9, 8, 7, 6, 5, 4}},
                .rows = 6,
                .columns = 6};
  matrix_t b = {
      .matrix = (double *[]){(double[]){11, 23, 45, 65, 78, 65},
                             (double[]){0.23, 0.74, 0.12, 0.32, 0.1, 0.2},
                             (double[]){7, 8, 1, 2, 6, 5},
                             (double[]){156, 651, 123, 321, 789, 987},
                             (double[]){735, 194, 732, 615, 679, 654},
                             (double[]){7.56, 12.5, 165, 1.23, 3.21, 7.56}},
      .rows = 6,
      .columns = 6};
  matrix_t expected = {
      .matrix =
          (double *[]){
              (double[]){4376.82, 3697.48, 5190.24, 4438.02, 6666.46, 7343.76},
              (double[]){2664.08, 2133.92, 3379.96, 2898.48, 4138.64, 4392.84},
              (double[]){8749.07, 7792.928, 9112.664, 9006.316, 13811.644,
                         15303.904},
              (double[]){7992.502, 6974.366, 8423.108, 8196.123, 12475.085,
                         13790.7},
              (double[]){5348.3, 4681.94, 6394.72, 5644.53, 8474.07, 9273.12},
              (double[]){4791.08, 5194.92, 5470.96, 5607.48, 8886.64, 9843.84}},
      .rows = 6,
      .columns = 6};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&res);
}

START_TEST(test_diff_dim_matrices) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2}, (double[]){3, 4},
                                       (double[]){5, 6}},
                .rows = 3,
                .columns = 2};
  matrix_t b = {.matrix = (double *[]){(double[]){9}, (double[]){8}},
                .rows = 2,
                .columns = 1};
  matrix_t expected = {
      .matrix = (double *[]){(double[]){25}, (double[]){59}, (double[]){93}},
      .rows = 3,
      .columns = 1};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&res);
}

// incorrect inputs

START_TEST(test_null_matrix) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2}, (double[]){3, 4},
                                       (double[]){5, 6}},
                .rows = 3,
                .columns = 2};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, NULL, &res), 1);
  ck_assert_int_eq(s21_mult_matrix(NULL, &a, &res), 1);
  ck_assert_int_eq(s21_mult_matrix(&a, &a, NULL), 1);
}
END_TEST

START_TEST(test_null_matrix_value) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2}, (double[]){3, 4},
                                       (double[]){5, 6}},
                .rows = 3,
                .columns = 2};
  matrix_t a_null = {.matrix = NULL, .rows = 3, .columns = 2};
  matrix_t b = {.matrix = (double *[]){(double[]){9}, (double[]){8}},
                .rows = 2,
                .columns = 1};
  matrix_t b_null = {.matrix = NULL, .rows = 2, .columns = 1};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, &b_null, &res), 1);
  ck_assert_int_eq(s21_mult_matrix(&a_null, &b, &res), 1);
}
END_TEST

START_TEST(test_null_matrix_row) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2}, (double[]){3, 4},
                                       (double[]){5, 6}},
                .rows = 3,
                .columns = 2};
  matrix_t a_null = {
      .matrix = (double *[]){(double[]){1, 2}, NULL, (double[]){5, 6}},
      .rows = 3,
      .columns = 2};
  matrix_t b = {.matrix = (double *[]){(double[]){9}, (double[]){8}},
                .rows = 2,
                .columns = 1};
  matrix_t b_null = {
      .matrix = (double *[]){(double[]){9}, NULL}, .rows = 2, .columns = 1};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, &b_null, &res), 1);
  ck_assert_int_eq(s21_mult_matrix(&a_null, &b, &res), 1);
}
END_TEST

// illegal matrix

START_TEST(test_cols_rows_mismatch) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2}, (double[]){3, 4},
                                       (double[]){5, 6}},
                .rows = 3,
                .columns = 2};
  matrix_t b = {
      .matrix = (double *[]){(double[]){9}, (double[]){8}, (double[]){7}},
      .rows = 3,
      .columns = 1};
  matrix_t res;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 2);
}

Suite *s21_mult_matrix_suite() {
  Suite *s = suite_create("s21_mult_matrix");

  TCase *positive_case = tcase_create("positive_case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_one_dim_matrices);
  tcase_add_test(positive_case, test_two_dim_matrices);
  tcase_add_test(positive_case, test_six_dim_matrices);
  tcase_add_test(positive_case, test_diff_dim_matrices);

  TCase *incorrect_inputs_tc = tcase_create("incorrect_inputs");
  suite_add_tcase(s, incorrect_inputs_tc);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_value);
  tcase_add_test(incorrect_inputs_tc, test_null_matrix_row);

  TCase *illegal_matrix_tc = tcase_create("illegal_matrix");
  suite_add_tcase(s, illegal_matrix_tc);
  tcase_add_test(illegal_matrix_tc, test_cols_rows_mismatch);

  return s;
}
