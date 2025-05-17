#include <stdlib.h>

#include "../s21_matrix.h"
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows <= 0 || columns <= 0) return ERROR;
  int exit_code = OK;

  double **matrix = calloc(rows, sizeof(double *));
  if (matrix == NULL) exit_code = ERROR;
  for (double **row = matrix; exit_code == OK && row < matrix + rows; row++) {
    *row = calloc(columns, sizeof(double));
    if (*row == NULL) exit_code = ERROR;
  }

  matrix_t res = (matrix_t){.matrix = matrix, .rows = rows, .columns = columns};
  if (exit_code == OK)
    *result = res;
  else if (exit_code == ERROR)
    s21_remove_matrix(&res);
  return exit_code;
}
