#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

class S21Matrix {
 private:
  int _rows, _cols;
  double* _p;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& o);
  S21Matrix(S21Matrix&& o);
  ~S21Matrix();

  int GetRows() const;
  void SetRows(int rows);
  int GetCols() const;
  void SetCols(int cols);

  bool operator==(const S21Matrix& o) const;
  double& operator()(int row, int col);
  double operator()(int row, int col) const;
  S21Matrix operator+(const S21Matrix& o) const;
  S21Matrix operator-(const S21Matrix& o) const;
  S21Matrix operator*(const S21Matrix& o) const;
  S21Matrix operator*(double num) const;
  friend S21Matrix operator*(const double num, const S21Matrix& o);
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix& operator*=(const double);
  S21Matrix& operator=(const S21Matrix& o);

  bool EqMatrix(const S21Matrix& o) const;
  void SumMatrix(const S21Matrix& o);
  void SubMatrix(const S21Matrix& o);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& o);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
};

#endif
