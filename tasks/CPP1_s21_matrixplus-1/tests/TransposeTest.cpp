#include <gtest/gtest.h>

#include "./utils/utils.hpp"

TEST(Transpose, HandleOneDimMatrix) {
  const int rows = 1, cols = 1;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{15.16}};
  double expected[][rows] = {{15.16}};
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.Transpose();
  checkmatrix(res, cols, rows, (double *)expected);
}

TEST(Transpose, HandleThreeDimMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.23, 4.56, 7.89},   // 0
                         {9.87, 6.54, 3.21},   // 1
                         {1.11, 4.44, 7.77}};  // 2

  double expected[][rows] = {{1.23, 9.87, 1.11},   // 0
                             {4.56, 6.54, 4.44},   // 1
                             {7.89, 3.21, 7.77}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.Transpose();
  checkmatrix(res, cols, rows, (double *)expected);
}

TEST(Transpose, HandleSymmMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.23, 4.56, 7.89},   // 0
                         {4.56, 6.54, 3.21},   // 1
                         {7.89, 3.21, 7.77}};  // 2

  double expected[][rows] = {{1.23, 4.56, 7.89},   // 0
                             {4.56, 6.54, 3.21},   // 1
                             {7.89, 3.21, 7.77}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.Transpose();
  checkmatrix(res, cols, rows, (double *)expected);
}

TEST(Transpose, HandleZeroMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{0, 0, 0},   // 0
                         {0, 0, 0},   // 1
                         {0, 0, 0}};  // 2

  double expected[][rows] = {{0, 0, 0},   // 0
                             {0, 0, 0},   // 1
                             {0, 0, 0}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.Transpose();
  checkmatrix(res, cols, rows, (double *)expected);
}

TEST(Transpose, HandleRectMatrix) {
  const int rows = 3, cols = 2;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{1.23, 4.56},   // 0
                         {9.87, 6.54},   // 1
                         {1.11, 4.44}};  // 2

  double expected[][rows] = {{1.23, 9.87, 1.11},   // 0
                             {4.56, 6.54, 4.44}};  // 1
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.Transpose();
  checkmatrix(res, cols, rows, (double *)expected);
}