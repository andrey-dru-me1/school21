#include <stdexcept>

#include "internal/utils.hpp"
#include "s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (compareDoubles(det, 0.))
    throw std::invalid_argument(
        "Matrix should have non-zero determinant to be inversed");

  S21Matrix complements = CalcComplements();
  S21Matrix adjugate_matrix = complements.Transpose();
  return adjugate_matrix * (1. / det);
}