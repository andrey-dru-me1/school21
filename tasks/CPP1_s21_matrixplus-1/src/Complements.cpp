#include <stdexcept>

#include "internal/utils.hpp"
#include "s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() const {
  if (_cols != _rows) {
    throw std::invalid_argument(
        "Matrix should be square for complements calculation");
  }
  int n = _cols;

  S21Matrix res(n, n);
  if (n == 1)
    res(0, 0) = 1.;
  else {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        S21Matrix submatrix = createSubmatrix(*this, i, j);
        double minor = submatrix.Determinant();
        double algebraic_complement = ((i + j) % 2 == 0) ? minor : -minor;
        res(i, j) = algebraic_complement;
      }
    }
  }
  return res;
}