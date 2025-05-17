#include <cstring>

#include "s21_matrix_oop.h"

template <typename T>
static T min(T a, T b) {
  return (a < b) ? a : b;
}

void S21Matrix::SetCols(int cols) {
  double *p = new double[cols * _rows]();
  std::memcpy(p, _p, sizeof(double) * (min(cols, _cols) * _rows));
  if (_p) delete[] _p;
  _p = p;
  _cols = cols;
}

void S21Matrix::SetRows(int rows) {
  double *p = new double[_cols * rows]();
  std::memcpy(p, _p, sizeof(double) * (_cols * min(rows, _rows)));
  if (_p) delete[] _p;
  _p = p;
  _rows = rows;
}