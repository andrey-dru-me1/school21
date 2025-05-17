#include "./utils.hpp"

#include <gtest/gtest.h>

void fillmatrix(S21Matrix &m, int rows, int cols, double *vals) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = vals[i * cols + j];
    }
  }
}

void checkmatrix(S21Matrix &m, int rows, int cols, double *expected) {
  ASSERT_EQ(m.GetRows(), rows);
  ASSERT_EQ(m.GetCols(), cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_NEAR(m(i, j), expected[i * cols + j], 1e-6);
    }
  }
}