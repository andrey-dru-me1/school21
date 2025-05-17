#include <gtest/gtest.h>

#include "./utils/utils.hpp"

TEST(Det, HandleOneDimMatrix) {
  const int rows = 1, cols = 1;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{15.63}};
  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_NEAR(m.Determinant(), 15.63, 1e-7);
}

TEST(Det, HandleTwoDimMatrix) {
  const int rows = 2, cols = 2;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.15, 2.16},   // 0
                         {3.17, 4.18}};  // 1
  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_NEAR(m.Determinant(), 1.15 * 4.18 - 2.16 * 3.17, 1e-7);
}

TEST(Det, HandleThreeDimMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.15, 2.16, 9.654},     // 0
                         {3.17, 4.18, 8.123},     // 1
                         {5.578, 6.485, 3.215}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_NEAR(m.Determinant(), 4.0998289, 1e-7);
}

TEST(Det, HandleIdMatrix) {
  const int rows = 6, cols = 6;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1, 0, 0, 0, 0, 0},   // 0
                         {0, 1, 0, 0, 0, 0},   // 1
                         {0, 0, 1, 0, 0, 0},   // 2
                         {0, 0, 0, 1, 0, 0},   // 3
                         {0, 0, 0, 0, 1, 0},   // 4
                         {0, 0, 0, 0, 0, 1}};  // 5
  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_NEAR(m.Determinant(), 1, 1e-7);
}

TEST(Det, HandleZeroMatrix) {
  const int rows = 6, cols = 6;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{0, 0, 0, 0, 0, 0},   // 0
                         {0, 0, 0, 0, 0, 0},   // 1
                         {0, 0, 0, 0, 0, 0},   // 2
                         {0, 0, 0, 0, 0, 0},   // 3
                         {0, 0, 0, 0, 0, 0},   // 4
                         {0, 0, 0, 0, 0, 0}};  // 5
  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_NEAR(m.Determinant(), 0, 1e-7);
}

TEST(Det, HandleLinaryDependantMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1, 2, 3},               // 0
                         {2, 4, 6},               // 1
                         {5.578, 6.485, 3.215}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_NEAR(m.Determinant(), 0, 1e-7);
}

TEST(Det, HandleRectDimMatrix) {
  const int rows = 3, cols = 4;
  S21Matrix m(rows, cols);
  ASSERT_ANY_THROW(m.Determinant());
}