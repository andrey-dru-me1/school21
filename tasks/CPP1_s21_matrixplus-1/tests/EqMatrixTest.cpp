#include <gtest/gtest.h>

#include "./utils/utils.hpp"

TEST(EqMatrix, HandleEquality) {
  const int rows = 3, cols = 3;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{1, 2, 3},   // 0
                          {4, 5, 6},   // 1
                          {7, 8, 9}};  // 2

  double bvals[][cols] = {{1, 2, 3},   // 0
                          {4, 5, 6},   // 1
                          {7, 8, 9}};  // 2

  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  ASSERT_EQ(a == b, true);
}

TEST(EqMatrix, HandleComplexEquality) {
  const int rows = 2, cols = 2;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1, 0.2},   // 0
                          {0.3, 0.4}};  // 1

  double bvals[][cols] = {{0.05 + 0.05, 0.3 - 0.1},  // 0
                          {0.2 + 0.1, 0.1 + 0.3}};   // 1

  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  ASSERT_EQ(a == b, true);
}

TEST(EqMatrix, HandleUnequality) {
  const int rows = 2, cols = 2;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{1, 2},   // 0
                          {3, 4}};  // 1

  double bvals[][cols] = {{5, 6},   // 0
                          {7, 8}};  // 1

  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  ASSERT_EQ(a == b, false);
}

TEST(EqMatrix, HandleSmallUnequality) {
  const int rows = 2, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1234567},   // 0
                          {0.7654321}};  // 1

  double bvals[][cols] = {{0.1234566},   // 0
                          {0.7654321}};  // 1

  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  ASSERT_EQ(a == b, false);
}

TEST(EqMatrix, HandleRectEquality) {
  const int rows = 2, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1234567}, {0.7654321}};

  double bvals[][cols] = {{0.1234565 + 2e-7}, {0.7654330 - 9e-7}};

  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  ASSERT_EQ(a == b, true);
}

TEST(EqMatrix, HandleRectEqualityFunction) {
  const int rows = 2, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1234567}, {0.7654321}};

  double bvals[][cols] = {{0.1234565 + 2e-7}, {0.7654330 - 9e-7}};

  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  ASSERT_EQ(a.EqMatrix(b), true);
}