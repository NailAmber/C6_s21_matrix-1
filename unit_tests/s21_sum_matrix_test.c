#include "s21_matrix_test.h"

START_TEST(sum_matrix_test1) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 2, &B), 0);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_test2) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 1, &B), 0);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_test3) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);
  fill_matrix(&B);
  text_matrix(&B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_test4) {
  ck_assert_int_eq(s21_sum_matrix(NULL, NULL, NULL), 1);
}
END_TEST

START_TEST(sum_matrix_test5) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);
  **(A.matrix) = NAN;
  fill_matrix(&B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_test6) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_test7) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(2, 1, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &B), 0);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_test8) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);
  fill_matrix(&B);
  **(B.matrix) = NAN;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_test9) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, NULL), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_sum_matrix(void) {
  Suite *s = suite_create("suite_sum_matrix");
  TCase *tc = tcase_create("sum_matrix_tc");

  tcase_add_test(tc, sum_matrix_test1);
  tcase_add_test(tc, sum_matrix_test2);
  tcase_add_test(tc, sum_matrix_test3);
  tcase_add_test(tc, sum_matrix_test4);
  tcase_add_test(tc, sum_matrix_test5);
  tcase_add_test(tc, sum_matrix_test6);
  tcase_add_test(tc, sum_matrix_test7);
  tcase_add_test(tc, sum_matrix_test8);
  tcase_add_test(tc, sum_matrix_test9);

  suite_add_tcase(s, tc);
  return s;
}