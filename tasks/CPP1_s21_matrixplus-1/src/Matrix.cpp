#include <cstring>

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : _rows(3), _cols(3) {
  _p = new double[_rows * _cols]();
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  _p = new double[_rows * _cols]();
}

S21Matrix::S21Matrix(const S21Matrix& o) : _rows(o._rows), _cols(o._cols) {
  *this = o;
}

S21Matrix::S21Matrix(S21Matrix&& o) : _rows(o._rows), _cols(o._cols), _p(o._p) {
  o._p = nullptr;
  o._rows = 0;
  o._cols = 0;
}

S21Matrix::~S21Matrix() {
  if (_p) {
    delete[] _p;
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (this != &o) {
    if (_p) delete[] _p;
    _rows = o._rows;
    _cols = o._cols;
    _p = new double[o._rows * o._cols]();
    std::memcpy(_p, o._p, o._rows * o._cols * sizeof(double));
  }
  return *this;
}