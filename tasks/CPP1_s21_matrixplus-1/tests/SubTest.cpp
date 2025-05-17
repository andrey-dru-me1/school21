#include <gtest/gtest.h>

#include "./utils/utils.hpp"

TEST(Sub, HandleSub) {
  const int rows = 3, cols = 3;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{1, 2, 3},   // 0
                          {4, 5, 6},   // 1
                          {7, 8, 9}};  // 2

  double bvals[][cols] = {{1, 2, 3},   // 0
                          {4, 5, 6},   // 1
                          {7, 8, 9}};  // 2

  double expected[][cols] = {{0, 0, 0},   // 0
                             {0, 0, 0},   // 1
                             {0, 0, 0}};  // 2
  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  S21Matrix res = a - b;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Sub, HandleZeroSub) {
  const int rows = 3, cols = 3;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{1, 2, 3},   // 0
                          {4, 5, 6},   // 1
                          {7, 8, 9}};  // 2

  double bvals[][cols] = {{0, 0, 0},   // 0
                          {0, 0, 0},   // 1
                          {0, 0, 0}};  // 2

  double expected[][cols] = {{1, 2, 3},   // 0
                             {4, 5, 6},   // 1
                             {7, 8, 9}};  // 2
  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  S21Matrix res = a - b;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Sub, HandleComplexSub) {
  const int rows = 2, cols = 2;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1, 0.2},   // 0
                          {0.3, 0.4}};  // 1

  double bvals[][cols] = {{0.05, 0.1},  // 0
                          {0.1, 156}};  // 1

  double expected[][cols] = {{0.05, 0.1},     // 0
                             {0.2, -155.6}};  // 1
  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  S21Matrix res = a - b;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Sub, HandleRectSub) {
  const int rows = 2, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1234567},   // 0
                          {0.7654321}};  // 1

  double bvals[][cols] = {{5e-7},   // 0
                          {8e-7}};  // 1

  double expected[][cols] = {{0.1234562},   // 0
                             {0.7654313}};  // 1
  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  S21Matrix res = a - b;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Sub, HandleBigRadixSub) {
  const int rows = 1, cols = 2;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{1234567e100, 7654321e79}};

  double bvals[][cols] = {{5e-7, 8e-7}};

  double expected[][cols] = {{1234567e100 - 5e-7, 7654321e79 - 8e-7}};
  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  S21Matrix res = a - b;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Sub, HandleMatrixMismatch) {
  const int rows = 1, cols = 2;
  S21Matrix a(rows, cols);
  S21Matrix b(cols, cols);
  double avals[][cols] = {{1234567e100, 7654321e79}};

  double bvals[][cols] = {{5e-7, 8e-7}};

  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  ASSERT_ANY_THROW(a - b);
}

TEST(Sub, HandleRectSubFunction) {
  const int rows = 2, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1234567},   // 0
                          {0.7654321}};  // 1

  double bvals[][cols] = {{5e-7},   // 0
                          {8e-7}};  // 1

  double expected[][cols] = {{0.1234562},   // 0
                             {0.7654313}};  // 1
  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  a.SubMatrix(b);
  checkmatrix(a, rows, cols, (double *)expected);
}

TEST(Sub, HandleRectSubMinusEq) {
  const int rows = 2, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  double avals[][cols] = {{0.1234567},   // 0
                          {0.7654321}};  // 1

  double bvals[][cols] = {{5e-7},   // 0
                          {8e-7}};  // 1

  double expected[][cols] = {{0.1234562},   // 0
                             {0.7654313}};  // 1
  fillmatrix(a, rows, cols, (double *)avals);
  fillmatrix(b, rows, cols, (double *)bvals);
  a -= b;
  checkmatrix(a, rows, cols, (double *)expected);
}
