#include <stddef.h>

#include "./../s21_matrix.h"
#include "./utils/utils.h"

#define EPS 1e-7

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (validate_matrix(A) == false || validate_matrix(B) == false)
    return FAILURE;
  int is_equal = SUCCESS;

  if (A->rows != B->rows || A->columns != B->columns) is_equal = FAILURE;
  int rows = A->rows, columns = B->columns;
  for (int i = 0; is_equal == SUCCESS && i < rows; i++) {
    for (int j = 0; is_equal == SUCCESS && j < columns; j++) {
      if (compare_doubles(A->matrix[i][j], B->matrix[i][j], EPS) != 0)
        is_equal = FAILURE;
    }
  }

  return is_equal;
}
