#include <stddef.h>

#include "../s21_matrix.h"
#include "./utils/utils.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (validate_matrix(A) == false || result == NULL) return ERROR;

  int exit_code = OK;
  matrix_t res;
  exit_code = s21_create_matrix(A->columns, A->rows, &res);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      res.matrix[j][i] = A->matrix[i][j];
    }
  }
  *result = res;
  return exit_code;
}
