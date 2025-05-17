#include <stdexcept>

#include "s21_matrix_oop.h"

double& S21Matrix::operator()(int row, int col) {
  if (row >= _rows || row < 0 || col >= _cols || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return _p[row * _cols + col];
}

double S21Matrix::operator()(int row, int col) const {
  if (row >= _rows || row < 0 || col >= _cols || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return _p[row * _cols + col];
}
