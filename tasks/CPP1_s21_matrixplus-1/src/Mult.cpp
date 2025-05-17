#include <stdexcept>

#include "s21_matrix_oop.h"

void S21Matrix::MulNumber(const double num) { *this *= num; }

void S21Matrix::MulMatrix(const S21Matrix& o) { *this *= o; }

S21Matrix S21Matrix::operator*(const S21Matrix& o) const {
  if (_cols != o._rows) {
    throw std::invalid_argument(
        "Incorrect input, matrices should be compatible for multiplication");
  }
  S21Matrix res(_rows, o._cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < o._cols; j++) {
      for (int k = 0; k < _cols; k++) {
        res(i, j) += (*this)(i, k) * o(k, j);
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      res(i, j) = (*this)(i, j) * num;
    }
  }
  return res;
}

S21Matrix operator*(const double num, const S21Matrix& o) { return o * num; }

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  *this = *this * o;
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  *this = *this * num;
  return *this;
}