
#include <stdio.h>

#include "s21_matrix.h"

int main(void) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);

  *(*(A.matrix + 0) + 0) = 2;
  *(*(A.matrix + 0) + 1) = 5;
  *(*(A.matrix + 0) + 2) = 7;

  *(*(A.matrix + 1) + 0) = 6;
  *(*(A.matrix + 1) + 1) = 3;
  *(*(A.matrix + 1) + 2) = 4;

  *(*(A.matrix + 2) + 0) = 5;
  *(*(A.matrix + 2) + 1) = -2;
  *(*(A.matrix + 2) + 2) = -3;
  /*
    *(*(Ref.matrix + 0) + 0) = 1;
    *(*(Ref.matrix + 0) + 1) = -1;
    *(*(Ref.matrix + 0) + 2) = 1;

    *(*(Ref.matrix + 1) + 0) = -38;
    *(*(Ref.matrix + 1) + 1) = 41;
    *(*(Ref.matrix + 1) + 2) = -34;

    *(*(Ref.matrix + 2) + 0) = 27;
    *(*(Ref.matrix + 2) + 1) = -29;
    *(*(Ref.matrix + 2) + 2) = 24;*/

  s21_inverse_matrix(&A, &B);
  text_matrix(&B);
  // s21_eq_matrix(&B, &Ref);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&Ref);
  return 0;
}