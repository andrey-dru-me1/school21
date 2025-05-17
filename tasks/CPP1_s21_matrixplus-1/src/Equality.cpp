#include <cstring>
#include <limits>

#include "internal/utils.hpp"
#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& o) const { return *this == o; }

bool S21Matrix::operator==(const S21Matrix& o) const {
  if (_rows != o._rows || _cols != o._cols) return false;
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      if (!compareDoubles((*this)(i, j), o(i, j))) return false;
    }
  }
  return true;
}