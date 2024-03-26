#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

int is_bad_size(const int rows, const int columns) {
  return rows < 1 || columns < 1;
}
int is_eq_size(const matrix_t *A, const matrix_t *B) {
  return A->columns == B->columns && A->rows == B->rows;
}

void fill_matrix(const matrix_t *A) {
  double count = 0.;
  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++, count += 1.1) {
      *(*(A->matrix + n) + m) = count;
    }
  }
}

void text_matrix(const matrix_t *A) {
  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      printf("%12.7lf ", *(*(A->matrix + n) + m));
    }
    printf("\n");
  }
  printf("\n");
}

int is_nan_inf_matrix(const matrix_t *A) {
  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      if (isnan(*(*(A->matrix + n) + m)) || isinf(*(*(A->matrix + n) + m))) {
        return 1;
      }
    }
  }
  return 0;
}

int is_mult_size(const matrix_t *A, const matrix_t *B) {
  return A->columns == B->rows;
}

int gaussian_elimination(const matrix_t *A, matrix_t *result) {
  copy_matrix(A, result);
  int swap_counter = 0;
  for (int m = 0, n = 0; m < A->columns; m++, n++) {
    swap_counter += sort_zeros(n, m, result);
    // printf("swaps = %d\n", swap_counter);
    //      text_matrix(result);
    for (int n1 = n + 1; n1 < A->rows; n1++) {
      if (*(*(result->matrix + n1) + m) > 0. ||
          *(*(result->matrix + n1) + m) < 0.) {
        double relation =
            *(*(result->matrix + n1) + m) / *(*(result->matrix + n) + m);
        for (int m1 = m; m1 < A->columns; m1++) {
          *(*(result->matrix + n1) + m1) -=
              relation * *(*(result->matrix + n) + m1);
        }
      } else {
        n1 = A->rows;
      }
    }
  }
  return swap_counter;
}

void inverse_gaussian_elimination(const matrix_t *A, matrix_t *result) {
  gaussian_elimination(A, result);
  for (int m = A->rows - 1, n = A->rows - 1; m >= 0; m--, n--) {
    for (int n1 = n - 1; n1 >= 0; n1--) {
      double div = *(*(result->matrix + n) + m);
      for (int m1 = m; m1 < A->columns; m1++) {
        *(*(result->matrix + n) + m1) /= div;
      }
      double relation =
          *(*(result->matrix + n1) + m) / *(*(result->matrix + n) + m);
      for (int m1 = m; m1 < A->columns; m1++) {
        *(*(result->matrix + n1) + m1) -=
            relation * *(*(result->matrix + n) + m1);
      }
    }
    if (n - 1 < 0) {
      double div = *(*(result->matrix + n) + m);
      for (int m1 = m; m1 < A->columns; m1++) {
        *(*(result->matrix + n) + m1) /= div;
      }
    }
  }
}

void swap_rows(const int n1, const int n2, matrix_t *A) {
  double *temp = *(A->matrix + n1);
  *(A->matrix + n1) = *(A->matrix + n2);
  *(A->matrix + n2) = temp;
}

int sort_zeros(const int n1, const int m, matrix_t *A) {
  int zero_row = -1;
  int swap_counter = 0;
  for (int n = n1; n < A->rows; n++) {
    if (fabs(*(*(A->matrix + n) + m)) < 1e-7 && zero_row == -1) {
      zero_row = n;
    } else if (zero_row > -1 && fabs(*(*(A->matrix + n) + m)) > 1e-7) {
      swap_rows(n, zero_row, A);
      swap_counter++;
      n = zero_row;
      zero_row = -1;
    }
  }
  return swap_counter;
}

void copy_matrix(const matrix_t *A, matrix_t *B) {
  s21_create_matrix(A->rows, A->columns, B);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      *(*(B->matrix + i) + j) = *(*(A->matrix + i) + j);
    }
  }
}

double first_minor(const int row, const int column, const matrix_t *A) {
  matrix_t minor;
  s21_create_matrix(A->rows - 1, A->rows - 1, &minor);

  int i = 0, j = 0;

  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      if (n != row && m != column) {
        *(*(minor.matrix + i) + j) = *(*(A->matrix + n) + m);
        j++;
      }
    }

    if (j != 0) {
      i++;
    }
    j = 0;
  }
  double result;
  s21_determinant(&minor, &result);
  s21_remove_matrix(&minor);
  return result;
}