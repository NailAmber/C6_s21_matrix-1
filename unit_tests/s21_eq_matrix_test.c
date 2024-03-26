#include "s21_matrix_test.h"

START_TEST(eq_matrix_test1) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  ck_assert_int_eq(s21_eq_matrix(NULL, &A), 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_matrix_test2) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_matrix_test3) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 2, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test4) { ck_assert_int_eq(s21_eq_matrix(NULL, NULL), 0); }
END_TEST

START_TEST(eq_matrix_test5) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 1, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test6) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 2, &B), 0);
  **(A.matrix) = 2;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_eq_matrix(void) {
  Suite *s = suite_create("suite_eq_matrix");
  TCase *tc = tcase_create("eq_matrix_tc");

  tcase_add_test(tc, eq_matrix_test1);
  tcase_add_test(tc, eq_matrix_test2);
  tcase_add_test(tc, eq_matrix_test3);
  tcase_add_test(tc, eq_matrix_test4);
  tcase_add_test(tc, eq_matrix_test5);
  tcase_add_test(tc, eq_matrix_test6);

  suite_add_tcase(s, tc);
  return s;
}