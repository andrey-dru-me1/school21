#include <stddef.h>

#include "../s21_matrix.h"
#include "./utils/utils.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (validate_matrix(A) == false || result == NULL) return ERROR;
  if (A->rows != A->columns) return CALC_ERR;
  double determinant;
  s21_determinant(A, &determinant);
  if (determinant == 0.) return CALC_ERR;

  matrix_t complements;
  s21_calc_complements(A, &complements);

  matrix_t adjugate_matrix;
  s21_transpose(&complements, &adjugate_matrix);

  s21_remove_matrix(&complements);

  s21_mult_number(&adjugate_matrix, 1. / determinant, result);

  s21_remove_matrix(&adjugate_matrix);

  return OK;
}
