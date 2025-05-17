#include <gtest/gtest.h>

#include "./utils/utils.hpp"

// positive case

TEST(CalcComplements, HandleOneDimMatrix) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 15.45;
  S21Matrix res = matrix.CalcComplements();
  ASSERT_EQ(res.GetRows(), 1);
  ASSERT_EQ(res.GetCols(), 1);
  ASSERT_DOUBLE_EQ(res(0, 0), 1.);
}

TEST(CalcComplements, HandleTwoDimMatrix) {
  const int rows = 2, cols = 2;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{11.12, 13.14}, {15.16, 17.18}};
  double expected[][cols] = {{17.18, -15.16}, {-13.14, 11.12}};
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.CalcComplements();
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(CalcComplements, HandleThreeDimMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{11.12, 13.14, 15.16},   // 0
                         {17.18, 19.20, 21.22},   // 1
                         {23.24, 25.26, 27.28}};  // 2

  double expected[][cols] = {{-12.2412, 24.4824, -12.2412},   // 0
                             {24.4824, -48.9648, 24.4824},    // 1
                             {-12.2412, 24.4824, -12.2412}};  // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.CalcComplements();
  checkmatrix(res, rows, cols, (double *)expected);
}

TEST(CalcComplements, HandleThreeDimAssymMatrix) {
  const int rows = 3, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{11.12, 13.14, 15.16},  // 0
                         {17.18, 19.20, 21.22},  // 1
                         {23.24, 0.26, 27.28}};  // 2

  double expected[][cols] = {{518.2588, 24.4824, -441.7412},   // 0
                             {-354.5176, -48.9648, 302.4824},  // 1
                             {-12.2412, 24.4824, -12.2412}};   // 2
  fillmatrix(m, rows, cols, (double *)vals);
  S21Matrix res = m.CalcComplements();
  checkmatrix(res, rows, cols, (double *)expected);
}

// illegal matrix

TEST(CalcComplements, HandleNonSquareMatrix) {
  const int rows = 2, cols = 3;
  S21Matrix m(rows, cols);
  double vals[][cols] = {{11.12, 13.14, 15.16},  // 0
                         {23.24, 0.26, 27.28}};  // 1
  fillmatrix(m, rows, cols, (double *)vals);
  ASSERT_ANY_THROW(m.CalcComplements());
}
