#include "s21_matrix_test.h"

START_TEST(transpose_test1) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(3, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &Ref), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 4;

  *(*(A.matrix + 1) + 0) = 2;
  *(*(A.matrix + 1) + 1) = 5;

  *(*(A.matrix + 2) + 0) = 3;
  *(*(A.matrix + 2) + 1) = 6;

  *(*(Ref.matrix + 0) + 0) = 1;
  *(*(Ref.matrix + 0) + 1) = 2;
  *(*(Ref.matrix + 0) + 2) = 3;

  *(*(Ref.matrix + 1) + 0) = 4;
  *(*(Ref.matrix + 1) + 1) = 5;
  *(*(Ref.matrix + 1) + 2) = 6;
  ck_assert_int_eq(s21_transpose(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(transpose_test2) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(4, 1, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 4, &Ref), 0);

  ck_assert_int_eq(s21_transpose(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(transpose_test3) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(3, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &Ref), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 4;

  *(*(A.matrix + 1) + 0) = 2;
  *(*(A.matrix + 1) + 1) = 5;

  *(*(A.matrix + 2) + 0) = 3;
  *(*(A.matrix + 2) + 1) = 6;

  *(*(Ref.matrix + 0) + 0) = 1;
  *(*(Ref.matrix + 0) + 1) = 2;
  *(*(Ref.matrix + 0) + 2) = 3;

  *(*(Ref.matrix + 1) + 0) = 4;
  *(*(Ref.matrix + 1) + 1) = 5;
  *(*(Ref.matrix + 1) + 2) = 6;

  ck_assert_int_eq(s21_transpose(&Ref, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &A), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(transpose_test4) { ck_assert_int_eq(s21_transpose(NULL, NULL), 1); }
END_TEST

START_TEST(transpose_test5) {
  matrix_t A;
  ck_assert_int_eq(s21_transpose(&A, NULL), 1);
}
END_TEST

START_TEST(transpose_test6) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(1, 1, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &Ref), 0);
  ck_assert_int_eq(s21_transpose(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

Suite *suite_transpose(void) {
  Suite *s = suite_create("suite_transpose");
  TCase *tc = tcase_create("transpose_tc");

  tcase_add_test(tc, transpose_test1);
  tcase_add_test(tc, transpose_test2);
  tcase_add_test(tc, transpose_test3);
  tcase_add_test(tc, transpose_test4);
  tcase_add_test(tc, transpose_test5);
  tcase_add_test(tc, transpose_test6);

  suite_add_tcase(s, tc);
  return s;
}