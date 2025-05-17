#include <gtest/gtest.h>

#include "./utils/utils.hpp"

TEST(MultNumber, HandleMultNumber) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1, 2, 3},   // 0
                         {4, 5, 6},   // 1
                         {7, 8, 9}};  // 2

  double expected[][cols] = {{2.3, 4.6, 6.9},      // 0
                             {9.2, 11.5, 13.8},    // 1
                             {16.1, 18.4, 20.7}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m * 2.3;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(MultNumber, HandleRectMultNumber) {
  const int rows = 2, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.2, 2.3, 3.4},   // 0
                         {4.5, 5.6, 6.7}};  // 1

  double expected[][cols] = {{-2.76, -5.29, -7.82},      // 0
                             {-10.35, -12.88, -15.41}};  // 1
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = -2.3 * m;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(MultNumber, HandleRectMultNumberPlusEq) {
  const int rows = 2, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.2, 2.3, 3.4},   // 0
                         {4.5, 5.6, 6.7}};  // 1

  double expected[][cols] = {{-2.76, -5.29, -7.82},      // 0
                             {-10.35, -12.88, -15.41}};  // 1
  fillmatrix(m, rows, cols, (double *)vals);
  m *= -2.3;
  checkmatrix(m, rows, cols, (double *)expected);
}

TEST(MultNumber, HandleRectMultNumberFunction) {
  const int rows = 2, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.2, 2.3, 3.4},   // 0
                         {4.5, 5.6, 6.7}};  // 1

  double expected[][cols] = {{-2.76, -5.29, -7.82},      // 0
                             {-10.35, -12.88, -15.41}};  // 1
  fillmatrix(m, rows, cols, (double *)vals);
  m.MulNumber(-2.3);
  checkmatrix(m, rows, cols, (double *)expected);
}

TEST(MultNumber, HandleMultOne) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1, 2, 3},   // 0
                         {4, 5, 6},   // 1
                         {7, 8, 9}};  // 2

  double expected[][cols] = {{1, 2, 3},   // 0
                             {4, 5, 6},   // 1
                             {7, 8, 9}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m * 1;
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(MultNumber, HandleMultZero) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1, 2, 3},   // 0
                         {4, 5, 6},   // 1
                         {7, 8, 9}};  // 2

  double expected[][cols] = {{0, 0, 0},   // 0
                             {0, 0, 0},   // 1
                             {0, 0, 0}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m * 0;
  checkmatrix(res, rows, cols, (double *)expected);
}