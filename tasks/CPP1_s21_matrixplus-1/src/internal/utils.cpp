#include "internal/utils.hpp"

#include <cstdlib>
#include <limits>

bool compareDoubles(const double a, const double b) {
  if (std::abs(a - b) < std::numeric_limits<double>::epsilon()) return true;
  return false;
}

S21Matrix createSubmatrix(const S21Matrix& o, int rowexc, int colexc) {
  S21Matrix res(o.GetRows() - 1, o.GetCols() - 1);
  int subi = 0;
  for (int i = 0; i < o.GetRows(); i++) {
    if (i == rowexc) continue;
    int subj = 0;
    for (int j = 0; j < o.GetCols(); j++) {
      if (j == colexc) continue;
      res(subi, subj) = o(i, j);
      subj++;
    }
    subi++;
  }
  return res;
}