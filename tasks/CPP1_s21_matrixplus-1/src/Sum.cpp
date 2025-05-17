#include <stdexcept>

#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& o) { *this += o; }

S21Matrix S21Matrix::operator+(const S21Matrix& o) const {
  if (_rows != o._rows || _cols != o._cols) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  S21Matrix res(_rows, _cols);
  for (auto i = 0; i < _rows; i++) {
    for (auto j = 0; j < _cols; j++) {
      res(i, j) = (*this)(i, j) + o(i, j);
    }
  }
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  *this = (*this) + o;
  return *this;
}