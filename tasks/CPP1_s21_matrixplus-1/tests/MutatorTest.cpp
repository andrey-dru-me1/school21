#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(SetRows, HandleSizeInc) {
  S21Matrix m(1, 1);
  m(0, 0) = 14;
  m.SetRows(3);
  ASSERT_EQ(m.GetRows(), 3);
  ASSERT_NEAR(m(0, 0), 14, 1e-7);
  ASSERT_NEAR(m(1, 0), 0, 1e-7);
  ASSERT_NEAR(m(2, 0), 0, 1e-7);
}

TEST(SetRows, HandleSizeDec) {
  S21Matrix m(3, 1);
  m(0, 0) = 14;
  m(2, 0) = 16;
  m.SetRows(1);
  ASSERT_EQ(m.GetRows(), 1);
  ASSERT_NEAR(m(0, 0), 14, 1e-7);
  ASSERT_ANY_THROW(m(1, 0));
  m.SetRows(3);
  ASSERT_NEAR(m(2, 0), 0, 1e-17);
}

TEST(SetCols, HandleSizeInc) {
  S21Matrix m(1, 1);
  m(0, 0) = 14;
  m.SetCols(3);
  ASSERT_EQ(m.GetCols(), 3);
  ASSERT_NEAR(m(0, 0), 14, 1e-7);
  ASSERT_NEAR(m(0, 1), 0, 1e-7);
  ASSERT_NEAR(m(0, 2), 0, 1e-7);
}

TEST(SetCols, HandleSizeDec) {
  S21Matrix m(1, 3);
  m(0, 0) = 14;
  m(0, 2) = 16;
  m.SetCols(1);
  ASSERT_EQ(m.GetCols(), 1);
  ASSERT_NEAR(m(0, 0), 14, 1e-7);
  ASSERT_ANY_THROW(m(0, 1));
  m.SetCols(3);
  ASSERT_NEAR(m(0, 2), 0, 1e-17);
}