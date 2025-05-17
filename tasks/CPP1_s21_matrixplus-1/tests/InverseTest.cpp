#include <gtest/gtest.h>

#include "./utils/utils.hpp"

TEST(Inverse, HandleOneDimMatrix) {
  const int rows = 1, cols = 1;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{15.16}};

  double expected[][cols] = {{1. / 15.16}};
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.InverseMatrix();
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Inverse, HandleTwoDimMatrix) {
  const int rows = 2, cols = 2;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{11.12, 13.14},   // 0
                         {15.16, 17.18}};  // 1

  double expected[][cols] = {{-2.1051858, 1.6101363},   // 0
                             {1.8576610, -1.3626115}};  // 1
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.InverseMatrix();
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Inverse, HandleThreeDimMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{11.12, 13.14, 15.16},  // 0
                         {18.17, 20.19, 21.22},  // 1
                         {3.21, 1.32, 2.13}};    // 2

  double expected[][cols] = {{-0.2283047, 0.1214586, 0.4149052},   // 0
                             {-0.4478621, 0.3803176, -0.6012910},  // 1
                             {0.6216132, -0.4187330, 0.2168349}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.InverseMatrix();
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(Inverse, HandleRectMatrix) {
  const int rows = 3, cols = 2;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{11.12, 13.14},  // 0
                         {18.17, 20.19},  // 1
                         {3.21, 1.32}};   // 2

  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_ANY_THROW(m.InverseMatrix());
}

TEST(Inverse, HandleZeroMatrix) {
  const int rows = 0, cols = 0;
  S21Matrix m(rows, cols);
  double vals[1];

  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_ANY_THROW(m.InverseMatrix());
}