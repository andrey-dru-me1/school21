#include <stdexcept>

#include "internal/utils.hpp"
#include "s21_matrix_oop.h"

double S21Matrix::Determinant() const {
  if (_cols != _rows) {
    throw std::invalid_argument("Matrix should be square for determinant");
  }
  int n = _cols;
  if (n == 1) return (*this)(0, 0);

  double res = 0.;
  for (int i = 0; i < _cols; i++) {
    S21Matrix submatrix = createSubmatrix(*this, 0, i);
    double minor = submatrix.Determinant();
    double algebraic_complement = (i % 2 == 0) ? minor : -minor;
    res += (*this)(0, i) * algebraic_complement;
  }
  return res;
}