#include <stddef.h>

#include "../s21_matrix.h"
#include "./utils/utils.h"

static int process_matrices(matrix_t *A, matrix_t *B, matrix_t *result,
                            double (*operation)(double, double)) {
  if (validate_matrix(A) == false || validate_matrix(B) == false ||
      result == NULL)
    return ERROR;

  int rows = A->rows, columns = A->columns;
  if (columns != B->columns || rows != B->rows) return CALC_ERR;

  int exit_code = OK;
  matrix_t res;
  exit_code = s21_create_matrix(rows, columns, &res);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      res.matrix[i][j] = operation(A->matrix[i][j], B->matrix[i][j]);
    }
  }
  *result = res;
  return exit_code;
}

static inline double plus(double a, double b) { return a + b; }

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return process_matrices(A, B, result, plus);
}

static inline double minus(double a, double b) { return a - b; }

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return process_matrices(A, B, result, minus);
}
