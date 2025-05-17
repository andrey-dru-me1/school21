#include <stddef.h>

#include "../s21_matrix.h"
#include "./utils/utils.h"

static int inner_det(matrix_t *A, double *result) {
  int n = A->columns;
  if (n == 1) {
    *result = A->matrix[0][0];
    return OK;
  }
  int exit_code = OK;

  double res = 0;
  for (int icolumn = 0; exit_code == OK && icolumn < A->columns; icolumn++) {
    matrix_t submatrix;
    if (exit_code == OK)
      exit_code = s21_create_matrix(n - 1, n - 1, &submatrix);
    if (exit_code == OK) fill_submatrix(A, &submatrix, 0, icolumn);
    double minor = 0;
    if (exit_code == OK) exit_code = inner_det(&submatrix, &minor);
    s21_remove_matrix(&submatrix);

    double algebraic_complement = minor;
    if (icolumn % 2 == 1) algebraic_complement *= -1;

    res += A->matrix[0][icolumn] * algebraic_complement;
  }
  *result = res;
  return exit_code;
}

int s21_determinant(matrix_t *A, double *result) {
  if (validate_matrix(A) == false || result == NULL) return ERROR;
  if (A->rows != A->columns) return CALC_ERR;
  return inner_det(A, result);
}
