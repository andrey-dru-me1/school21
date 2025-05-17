#ifndef S21_MATRIX_H_3634589
#define S21_MATRIX_H_3634589

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// 0 - OK
// 1 - Error, incorrect matrix
// 2 - Calculation error (mismatched matrix sizes; matrix for which calculations
// cannot be performed, etc.)
#define OK 0
#define ERROR 1
#define CALC_ERR 2

int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif
