#include <stdlib.h>

#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL || A->matrix == NULL) return;
  for (double **row = A->matrix; row < A->matrix + A->rows; row++) {
    free(*row);
    *row = NULL;
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}
