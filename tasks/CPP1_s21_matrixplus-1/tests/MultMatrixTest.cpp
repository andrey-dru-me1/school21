#include <gtest/gtest.h>

#include "./utils/utils.hpp"

TEST(MultMatrix, HandleMultOneDimMatrices) {
  const int k = 1, l = 1, n = 1;
  S21Matrix a(k, l);
  S21Matrix b(l, n);
  double avals[][l] = {{15.16}};

  double bvals[][n] = {{17.18}};

  double expected[][n] = {{15.16 * 17.18}};
  fillmatrix(a, k, l, (double *)avals);
  fillmatrix(b, l, n, (double *)bvals);
  S21Matrix res = a * b;
  checkmatrix(res, k, n, (double *)expected);
}

TEST(MultMatrix, HandleMultTwoDimMatrices) {
  const int k = 2, l = 2, n = 2;
  S21Matrix a(k, l);
  S21Matrix b(l, n);
  double avals[][l] = {{15.16, 17.18},   // 0
                       {19.20, 20.21}};  // 1

  double bvals[][n] = {{21.22, 23.24},   // 0
                       {25.26, 27.28}};  // 1

  double expected[][n] = {
      {15.16 * 21.22 + 17.18 * 25.26, 15.16 * 23.24 + 17.18 * 27.28},   // 0
      {19.20 * 21.22 + 20.21 * 25.26, 19.20 * 23.24 + 20.21 * 27.28}};  // 1
  fillmatrix(a, k, l, (double *)avals);
  fillmatrix(b, l, n, (double *)bvals);
  S21Matrix res = a * b;
  checkmatrix(res, k, n, (double *)expected);
}

TEST(MultMatrix, HandleRectMatrices) {
  const int k = 3, l = 2, n = 1;
  S21Matrix a(k, l);
  S21Matrix b(l, n);
  double avals[][l] = {{1, 2},   // 0
                       {3, 4},   // 1
                       {5, 6}};  // 2

  double bvals[][n] = {{9}, {8}};

  double expected[][n] = {{25}, {59}, {93}};
  fillmatrix(a, k, l, (double *)avals);
  fillmatrix(b, l, n, (double *)bvals);
  S21Matrix res = a * b;
  checkmatrix(res, k, n, (double *)expected);
}

TEST(MultMatrix, HandleMultSixDimMatrices) {
  const int k = 6, l = 6, n = 6;
  S21Matrix a(k, l);
  S21Matrix b(l, n);
  double avals[][l] = {{1, 2, 3, 4, 5, 6},              // 0
                       {6, 8, 7, 2, 3, 4},              // 1
                       {1.1, 2.2, 7.7, 8.8, 9.9, 4.4},  // 2
                       {1.2, 3.4, 5.6, 7.8, 9.1, 4.5},  // 3
                       {5, 6, 7, 5, 6, 7},              // 4
                       {9, 8, 7, 6, 5, 4}};             // 5

  double bvals[][n] = {{11, 23, 45, 65, 78, 65},              // 0
                       {0.23, 0.74, 0.12, 0.32, 0.1, 0.2},    // 1
                       {7, 8, 1, 2, 6, 5},                    // 2
                       {156, 651, 123, 321, 789, 987},        // 3
                       {735, 194, 732, 615, 679, 654},        // 4
                       {7.56, 12.5, 165, 1.23, 3.21, 7.56}};  // 5

  double expected[][n] = {
      {4376.82, 3697.48, 5190.24, 4438.02, 6666.46, 7343.76},         // 0
      {2664.08, 2133.92, 3379.96, 2898.48, 4138.64, 4392.84},         // 1
      {8749.07, 7792.928, 9112.664, 9006.316, 13811.644, 15303.904},  // 2
      {7992.502, 6974.366, 8423.108, 8196.123, 12475.085, 13790.7},   // 3
      {5348.3, 4681.94, 6394.72, 5644.53, 8474.07, 9273.12},          // 4
      {4791.08, 5194.92, 5470.96, 5607.48, 8886.64, 9843.84}};        // 5
  fillmatrix(a, k, l, (double *)avals);
  fillmatrix(b, l, n, (double *)bvals);
  S21Matrix res = a * b;
  checkmatrix(res, k, n, (double *)expected);
}

TEST(MultMatrix, HandleRectMatricesFunction) {
  const int k = 3, l = 2, n = 1;
  S21Matrix a(k, l);
  S21Matrix b(l, n);
  double avals[][l] = {{1, 2},   // 0
                       {3, 4},   // 1
                       {5, 6}};  // 2

  double bvals[][n] = {{9}, {8}};

  double expected[][n] = {{25}, {59}, {93}};
  fillmatrix(a, k, l, (double *)avals);
  fillmatrix(b, l, n, (double *)bvals);
  a.MulMatrix(b);
  checkmatrix(a, k, n, (double *)expected);
}

TEST(MultMatrix, HandleRectMatricesMultEq) {
  const int k = 3, l = 2, n = 1;
  S21Matrix a(k, l);
  S21Matrix b(l, n);
  double avals[][l] = {{1, 2},   // 0
                       {3, 4},   // 1
                       {5, 6}};  // 2

  double bvals[][n] = {{9}, {8}};

  double expected[][n] = {{25}, {59}, {93}};
  fillmatrix(a, k, l, (double *)avals);
  fillmatrix(b, l, n, (double *)bvals);
  a *= b;
  checkmatrix(a, k, n, (double *)expected);
}

TEST(MultMatrix, HandleMatrixMismatch) {
  S21Matrix a(3, 2);
  S21Matrix b(3, 1);
  double avals[][2] = {{1, 2},   // 0
                       {3, 4},   // 1
                       {5, 6}};  // 2

  double bvals[][1] = {{9}, {8}, {7}};

  fillmatrix(a, 3, 2, (double *)avals);
  fillmatrix(b, 3, 1, (double *)bvals);
  ASSERT_ANY_THROW(a * b);
}