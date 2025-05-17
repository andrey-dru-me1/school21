#ifndef MATRIX_UTILS_H_0263487
#define MATRIX_UTILS_H_0263487

#include <stdbool.h>

#include "../../s21_matrix.h"

char compare_doubles(double a, double b, double eps);

bool validate_matrix(matrix_t *matrix);

void fill_submatrix(matrix_t *src, matrix_t *dst, int row, int column);

#endif
