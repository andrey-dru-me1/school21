#include <stddef.h>

#include "../s21_matrix.h"
#include "./utils/utils.h"

inline static int calc_big_matrix_complements(matrix_t *A, matrix_t *result) {
  int exit_code = OK;
  int n = A->rows;

  for (int i = 0; exit_code == OK && i < n; i++) {
    for (int j = 0; exit_code == OK && j < n; j++) {
      matrix_t submatrix;
      if (exit_code == OK)
        exit_code = s21_create_matrix(n - 1, n - 1, &submatrix);
      if (exit_code == OK) fill_submatrix(A, &submatrix, i, j);
      double minor = 0;
      if (exit_code == OK) exit_code = s21_determinant(&submatrix, &minor);
      if ((i + j) % 2 == 1) minor = -minor;
      result->matrix[i][j] = minor;
      s21_remove_matrix(&submatrix);
    }
  }
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (validate_matrix(A) == false || result == NULL) return ERROR;
  if (A->columns != A->rows) return CALC_ERR;

  int exit_code = OK;

  int n = A->rows;
  matrix_t res;
  exit_code = s21_create_matrix(n, n, &res);

  if (exit_code == OK && A->columns == 1)
    res.matrix[0][0] = 1.;
  else
    exit_code = calc_big_matrix_complements(A, &res);

  *result = res;
  return exit_code;
}
