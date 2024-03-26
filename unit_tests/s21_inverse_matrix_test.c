#include <check.h>

#include "s21_matrix_test.h"

START_TEST(inverse_matrix_test1) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(1, 1, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &Ref), 0);

  *(*(A.matrix + 0) + 0) = -64;

  *(*(Ref.matrix + 0) + 0) = -0.015625;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(inverse_matrix_test2) {}
END_TEST

START_TEST(inverse_matrix_test3) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(4, 4, &A), 0);
  ck_assert_int_eq(s21_create_matrix(4, 4, &Ref), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 66;
  *(*(A.matrix + 0) + 2) = 4;
  *(*(A.matrix + 0) + 3) = 2;

  *(*(A.matrix + 1) + 0) = 1;
  *(*(A.matrix + 1) + 1) = 2;
  *(*(A.matrix + 1) + 2) = 6;
  *(*(A.matrix + 1) + 3) = 2;

  *(*(A.matrix + 2) + 0) = 2;
  *(*(A.matrix + 2) + 1) = 1;
  *(*(A.matrix + 2) + 2) = 8;
  *(*(A.matrix + 2) + 3) = 8;

  *(*(A.matrix + 3) + 0) = 2;
  *(*(A.matrix + 3) + 1) = 1;
  *(*(A.matrix + 3) + 2) = 9;
  *(*(A.matrix + 3) + 3) = 4;

  *(*(Ref.matrix + 0) + 0) = 0.0681818;
  *(*(Ref.matrix + 0) + 1) = -3.3106061;
  *(*(Ref.matrix + 0) + 2) = -0.5;
  *(*(Ref.matrix + 0) + 3) = 2.6212121;

  *(*(Ref.matrix + 1) + 0) = 0.0151515;
  *(*(Ref.matrix + 1) + 1) = 0.0050505;
  *(*(Ref.matrix + 1) + 2) = 0;
  *(*(Ref.matrix + 1) + 3) = -0.0101010;

  *(*(Ref.matrix + 2) + 0) = -0.0151515;
  *(*(Ref.matrix + 2) + 1) = 0.6616162;
  *(*(Ref.matrix + 2) + 2) = 0;
  *(*(Ref.matrix + 2) + 3) = -0.3232323;

  *(*(Ref.matrix + 3) + 0) = -0.0037879;
  *(*(Ref.matrix + 3) + 1) = 0.1654040;
  *(*(Ref.matrix + 3) + 2) = 0.25;
  *(*(Ref.matrix + 3) + 3) = -0.3308081;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(inverse_matrix_test4) {
  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), 1);
}
END_TEST

START_TEST(inverse_matrix_test5) {
  matrix_t A;
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), 1);
}
END_TEST

START_TEST(inverse_matrix_test6) {
  matrix_t A, B;
  s21_create_matrix(4, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_test_zero_row) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &Ref), 0);

  *(*(A.matrix + 0) + 0) = 2;
  *(*(A.matrix + 0) + 1) = 5;
  *(*(A.matrix + 0) + 2) = 7;

  *(*(A.matrix + 1) + 0) = 6;
  *(*(A.matrix + 1) + 1) = 3;
  *(*(A.matrix + 1) + 2) = 4;

  *(*(A.matrix + 2) + 0) = 5;
  *(*(A.matrix + 2) + 1) = -2;
  *(*(A.matrix + 2) + 2) = -3;

  *(*(Ref.matrix + 0) + 0) = 1;
  *(*(Ref.matrix + 0) + 1) = -1;
  *(*(Ref.matrix + 0) + 2) = 1;

  *(*(Ref.matrix + 1) + 0) = -38;
  *(*(Ref.matrix + 1) + 1) = 41;
  *(*(Ref.matrix + 1) + 2) = -34;

  *(*(Ref.matrix + 2) + 0) = 27;
  *(*(Ref.matrix + 2) + 1) = -29;
  *(*(Ref.matrix + 2) + 2) = 24;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(inverse_matrix_test_singular_matrix) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(1, 1, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &Ref), 0);

  *(*(A.matrix + 0) + 0) = 0;

  *(*(Ref.matrix + 0) + 0) = 0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Ref);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc = tcase_create("inverse_matrix_tc");

  tcase_add_test(tc, inverse_matrix_test1);
  tcase_add_test(tc, inverse_matrix_test2);
  tcase_add_test(tc, inverse_matrix_test3);
  tcase_add_test(tc, inverse_matrix_test4);
  tcase_add_test(tc, inverse_matrix_test5);
  tcase_add_test(tc, inverse_matrix_test6);
  tcase_add_test(tc, inverse_matrix_test_zero_row);
  tcase_add_test(tc, inverse_matrix_test_singular_matrix);

  suite_add_tcase(s, tc);
  return s;
}