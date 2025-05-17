#include <stddef.h>

#include "../s21_matrix.h"
#include "./utils/utils.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (validate_matrix(A) == false || validate_matrix(B) == false ||
      result == NULL)
    return ERROR;
  if (A->columns != B->rows) return CALC_ERR;

  int exit_code = OK;
  int l = A->rows, m = A->columns, n = B->columns;
  matrix_t res;
  exit_code = s21_create_matrix(l, n, &res);

  for (int i = 0; i < l; i++) {
    for (int j = 0; j < n; j++) {
      double res_ij = 0;
      for (int r = 0; r < m; r++) {
        res_ij += A->matrix[i][r] * B->matrix[r][j];
      }
      res.matrix[i][j] = res_ij;
    }
  }
  *result = res;
  return exit_code;
}
