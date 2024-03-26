#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || is_bad_size(rows, columns)) {
    return 1;
  }

  result->matrix = (double **)calloc((size_t)rows, sizeof(double *));
  int pt = 0;
  for (; pt < rows; pt++) {
    *(result->matrix + pt) = (double *)calloc((size_t)columns, sizeof(double));
  }
  result->rows = rows;
  result->columns = columns;

  return 0;
}
// Удаление матрицы
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->columns > 0 && A->rows > 0) {
    for (int i = 0; i < A->rows; i++) {
      free(*(A->matrix + i));
    }
    free(A->matrix);
  }
}

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || !is_eq_size(A, B)) {
    return FAILURE;
  }

  int res = SUCCESS;

  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      double a = *(*(A->matrix + n) + m);
      double b = *(*(B->matrix + n) + m);
      if (fabs(a - b) > 1e-7 || isnan(a) || isnan(b)) {
        res = FAILURE;
        n = A->rows;
        m = B->columns;
      }
    }
  }

  return res;
}

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return 1;
  }

  if (!is_eq_size(A, B)) {
    return 2;
  }

  s21_create_matrix(A->rows, A->columns, result);

  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      *(*(result->matrix + n) + m) =
          *(*(A->matrix + n) + m) + *(*(B->matrix + n) + m);
    }
  }

  return 0;
}
// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return 1;
  }

  if (!is_eq_size(A, B)) {
    return 2;
  }

  s21_create_matrix(A->rows, A->columns, result);

  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      *(*(result->matrix + n) + m) =
          *(*(A->matrix + n) + m) - *(*(B->matrix + n) + m);
    }
  }

  return 0;
}

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return 1;
  }

  if (isnan(number)) {
    return 2;
  }

  s21_create_matrix(A->rows, A->columns, result);

  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      *(*(result->matrix + n) + m) = *(*(A->matrix + n) + m) * number;
    }
  }

  return 0;
}
// Умножение матрицы на матрицу
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return 1;
  }

  if (!is_mult_size(A, B) || is_nan_inf_matrix(A) || is_nan_inf_matrix(B)) {
    return 2;
  }

  s21_create_matrix(A->rows, B->columns, result);

  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < B->columns; m++) {
      for (int i = 0; i < A->columns; i++) {
        *(*(result->matrix + n) + m) +=
            *(*(A->matrix + n) + i) * *(*(B->matrix + i) + m);
      }
    }
  }
  return 0;
}

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return 1;
  }

  s21_create_matrix(A->columns, A->rows, result);

  for (int n = 0; n < A->columns; n++) {
    for (int m = 0; m < A->rows; m++) {
      *(*(result->matrix + n) + m) = *(*(A->matrix + m) + n);
    }
  }
  return 0;
}

// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return 1;
  } else if (A->columns != A->rows) {
    return 2;
  }
  s21_create_matrix(A->rows, A->rows, result);

  if (A->rows == 1) {
    **result->matrix = **A->matrix;
  } else {
    for (int n = 0; n < A->rows; n++) {
      for (int m = 0; m < A->rows; m++) {
        *(*(result->matrix + n) + m) = first_minor(n, m, A);
        if (((n + m) % 2) == 1) {
          *(*(result->matrix + n) + m) *= -1;
        }
      }
    }
  }

  return 0;
}

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || result == NULL) {
    return 1;
  } else if (A->columns != A->rows) {
    return 2;
  }
  matrix_t res;
  int swap_counter = gaussian_elimination(A, &res);
  *result = 1;
  if (swap_counter % 2 == 1) {
    *result = -*result;
  }
  for (int n = 0, m = 0; n < A->rows; n++, m++) {
    *result *= *(*(res.matrix + n) + m);
  }
  s21_remove_matrix(&res);
  return 0;
}

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return 1;
  }
  {
    double d = 0;
    s21_determinant(A, &d);
    if (A->columns != A->rows || fabs(d) < 1e-7) {
      return 2;
    }
  }
  s21_create_matrix(A->rows, A->columns, result);
  if (A->rows == 1) {
    **result->matrix = pow(**A->matrix, -1);
  } else {
    matrix_t augmented;
    s21_create_matrix(A->rows, A->columns * 2, &augmented);
    for (int n = 0; n < A->rows; n++) {
      for (int m = 0; m < A->columns; m++) {
        *(*(augmented.matrix + n) + m) = *(*(A->matrix + n) + m);
        *(*(augmented.matrix + n) + m + A->columns) = n == m ? 1 : 0;
      }
    }
    matrix_t eliminated;
    inverse_gaussian_elimination(&augmented, &eliminated);

    for (int n = 0; n < A->rows; n++) {
      for (int m = 0; m < A->columns; m++) {
        *(*(result->matrix + n) + m) =
            *(*(eliminated.matrix + n) + m + A->columns);
      }
    }
    s21_remove_matrix(&augmented);
    s21_remove_matrix(&eliminated);
  }
  return 0;
}