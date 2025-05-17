#include "utils.h"

#include <stddef.h>

char compare_doubles(double a, double b, double eps) {
  long double diff = (long double)a - b;
  char res;
  if (diff > -eps && diff < eps)
    res = 0;
  else if (a > b)
    res = 1;
  else
    res = -1;
  return res;
}

bool validate_matrix(matrix_t *matrix) {
  if (matrix == NULL || matrix->matrix == NULL || matrix->rows <= 0 ||
      matrix->columns <= 0)
    return false;
  for (int i = 0; i < matrix->rows; i++) {
    if (matrix->matrix[i] == NULL) return false;
  }
  return true;
}

void fill_submatrix(matrix_t *src, matrix_t *dst, int row, int column) {
  int n = src->rows;
  int subi = 0;
  for (int i = 0; i < n; i++) {
    if (i == row) continue;
    int subj = 0;
    for (int j = 0; j < n; j++) {
      if (j == column) continue;
      dst->matrix[subi][subj] = src->matrix[i][j];
      subj++;
    }
    subi++;
  }
}
