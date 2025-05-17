#include "../s21_matrix.h"
#include "test.h"

// Positive tests

START_TEST(test_simple_equality) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2, 3}, (double[]){4, 5, 6},
                                       (double[]){7, 8, 9}},
                .rows = 3,
                .columns = 3};
  matrix_t b = a;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
}
END_TEST

START_TEST(test_complex_equality) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1, 0.2}, (double[]){0.3, 0.4}},
      .rows = 2,
      .columns = 2};
  matrix_t b = {.matrix = (double *[]){(double[]){0.05 + 0.05, 0.3 - 0.1},
                                       (double[]){0.2 + 0.1, 0.1 + 0.3}},
                .rows = 2,
                .columns = 2};
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
}
END_TEST

START_TEST(test_diff_dim_eq) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t b = {.matrix = (double *[]){(double[]){0.1234565 + 2e-7},
                                       (double[]){0.7654330 - 9e-7}},
                .rows = 2,
                .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
}
END_TEST

// Negative tests

START_TEST(test_simple_diff) {
  matrix_t a = {.matrix = (double *[]){(double[]){1, 2}, (double[]){3, 4}},
                .rows = 2,
                .columns = 2};
  matrix_t b = {.matrix = (double *[]){(double[]){5, 6}, (double[]){7, 8}},
                .rows = 2,
                .columns = 2};
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
}
END_TEST

START_TEST(test_small_diff) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t b = {
      .matrix = (double *[]){(double[]){0.1234566}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
}
END_TEST

// Incorrect inputs

START_TEST(test_fst_null) {
  matrix_t b = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(NULL, &b), FAILURE);
}
END_TEST

START_TEST(test_snd_null) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(&a, NULL), FAILURE);
}
END_TEST

START_TEST(test_both_null) { ck_assert_int_eq(s21_eq_matrix(NULL, NULL), 0); }
END_TEST

START_TEST(test_matrix_null) {
  matrix_t a = {.matrix = NULL, .rows = 2, .columns = 1};
  matrix_t b = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
}
END_TEST

START_TEST(test_inner_null) {
  matrix_t a = {
      .matrix = (double *[]){(double[]){0.1234567}, (double[]){0.7654321}},
      .rows = 2,
      .columns = 1};
  matrix_t b = {.matrix = (double *[]){(double[]){0.1234567}, NULL},
                .rows = 2,
                .columns = 1};
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
}
END_TEST

Suite *s21_eq_matrix_suite() {
  Suite *s = suite_create("s21_eq_matrix");

  TCase *positive_case = tcase_create("positive case");
  suite_add_tcase(s, positive_case);
  tcase_add_test(positive_case, test_simple_equality);
  tcase_add_test(positive_case, test_complex_equality);
  tcase_add_test(positive_case, test_diff_dim_eq);

  TCase *negative_case = tcase_create("negative case");
  suite_add_tcase(s, negative_case);
  tcase_add_test(negative_case, test_simple_diff);
  tcase_add_test(negative_case, test_small_diff);

  TCase *incorrect_case = tcase_create("incorrect case");
  suite_add_tcase(s, incorrect_case);
  tcase_add_test(incorrect_case, test_fst_null);
  tcase_add_test(incorrect_case, test_snd_null);
  tcase_add_test(incorrect_case, test_both_null);
  tcase_add_test(incorrect_case, test_matrix_null);
  tcase_add_test(incorrect_case, test_inner_null);

  return s;
}
