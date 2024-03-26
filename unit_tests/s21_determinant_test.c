#include <check.h>

#include "s21_matrix_test.h"

START_TEST(determinant_test1) {
  matrix_t A;
  double result;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);

  *(*(A.matrix + 0) + 0) = 2;
  *(*(A.matrix + 0) + 1) = 3;
  *(*(A.matrix + 0) + 2) = 1;

  *(*(A.matrix + 1) + 0) = 6;
  *(*(A.matrix + 1) + 1) = 5;
  *(*(A.matrix + 1) + 2) = 2;

  *(*(A.matrix + 2) + 0) = 1;
  *(*(A.matrix + 2) + 1) = 4;
  *(*(A.matrix + 2) + 2) = 7;

  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  ck_assert_double_eq(result, -47.);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test2) {
  matrix_t A;
  double result;
  ck_assert_int_eq(s21_create_matrix(3, 4, &A), 0);

  ck_assert_int_eq(s21_determinant(&A, &result), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test3) {
  matrix_t A;
  double result;
  ck_assert_int_eq(s21_create_matrix(4, 4, &A), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 3;
  *(*(A.matrix + 0) + 2) = 5;
  *(*(A.matrix + 0) + 3) = 9;

  *(*(A.matrix + 1) + 0) = 1;
  *(*(A.matrix + 1) + 1) = 3;
  *(*(A.matrix + 1) + 2) = 1;
  *(*(A.matrix + 1) + 3) = 7;

  *(*(A.matrix + 2) + 0) = 4;
  *(*(A.matrix + 2) + 1) = 3;
  *(*(A.matrix + 2) + 2) = 9;
  *(*(A.matrix + 2) + 3) = 7;

  *(*(A.matrix + 3) + 0) = 5;
  *(*(A.matrix + 3) + 1) = 2;
  *(*(A.matrix + 3) + 2) = 0;
  *(*(A.matrix + 3) + 3) = 9;

  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  ck_assert_double_eq_tol(result, -376., 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test4) {
  ck_assert_int_eq(s21_determinant(NULL, NULL), 1);
}
END_TEST

START_TEST(determinant_test5) {
  matrix_t A;
  ck_assert_int_eq(s21_determinant(&A, NULL), 1);
}
END_TEST

START_TEST(determinant_test6) {
  matrix_t A;
  double result;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 0;
  *(*(A.matrix + 0) + 2) = 0;

  *(*(A.matrix + 1) + 0) = 0;
  *(*(A.matrix + 1) + 1) = 1;
  *(*(A.matrix + 1) + 2) = 0;

  *(*(A.matrix + 2) + 0) = 0;
  *(*(A.matrix + 2) + 1) = 0;
  *(*(A.matrix + 2) + 2) = 1;

  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  ck_assert_double_eq_tol(result, 1.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_zero_row) {
  matrix_t A;
  double result;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 2;
  *(*(A.matrix + 0) + 2) = 3;

  *(*(A.matrix + 1) + 0) = 0;
  *(*(A.matrix + 1) + 1) = 0;
  *(*(A.matrix + 1) + 2) = 0;

  *(*(A.matrix + 2) + 0) = 4;
  *(*(A.matrix + 2) + 1) = 5;
  *(*(A.matrix + 2) + 2) = 6;

  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_singular_matrix) {
  matrix_t A;
  double result;
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);

  *(*(A.matrix + 0) + 0) = 2;
  *(*(A.matrix + 0) + 1) = 4;

  *(*(A.matrix + 1) + 0) = 1;
  *(*(A.matrix + 1) + 1) = 2;

  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_determinant(void) {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("determinant_tc");

  tcase_add_test(tc, determinant_test1);
  tcase_add_test(tc, determinant_test2);
  tcase_add_test(tc, determinant_test3);
  tcase_add_test(tc, determinant_test4);
  tcase_add_test(tc, determinant_test5);
  tcase_add_test(tc, determinant_test6);
  tcase_add_test(tc, determinant_test_zero_row);
  tcase_add_test(tc, determinant_test_singular_matrix);

  suite_add_tcase(s, tc);
  return s;
}