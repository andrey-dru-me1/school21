#include "s21_matrix_oop.h"

void S21Matrix::SubMatrix(const S21Matrix& o) { *this -= o; }

S21Matrix S21Matrix::operator-(const S21Matrix& o) const {
  return *this + (-1) * o;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  (*this) = *this - o;
  return *this;
}