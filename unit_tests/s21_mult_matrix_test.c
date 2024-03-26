#include "s21_matrix_test.h"

START_TEST(mult_matrix_test1) {
  matrix_t A, B, C, Ref;
  ck_assert_int_eq(s21_create_matrix(4, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), 0);
  ck_assert_int_eq(s21_create_matrix(4, 3, &Ref), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 0;
  *(*(A.matrix + 0) + 2) = 1;

  *(*(A.matrix + 1) + 0) = 2;
  *(*(A.matrix + 1) + 1) = 1;
  *(*(A.matrix + 1) + 2) = 1;

  *(*(A.matrix + 2) + 0) = 0;
  *(*(A.matrix + 2) + 1) = 1;
  *(*(A.matrix + 2) + 2) = 1;

  *(*(A.matrix + 3) + 0) = 1;
  *(*(A.matrix + 3) + 1) = 1;
  *(*(A.matrix + 3) + 2) = 2;

  *(*(B.matrix + 0) + 0) = 1;
  *(*(B.matrix + 0) + 1) = 2;
  *(*(B.matrix + 0) + 2) = 1;

  *(*(B.matrix + 1) + 0) = 2;
  *(*(B.matrix + 1) + 1) = 3;
  *(*(B.matrix + 1) + 2) = 1;

  *(*(B.matrix + 2) + 0) = 4;
  *(*(B.matrix + 2) + 1) = 2;
  *(*(B.matrix + 2) + 2) = 2;

  *(*(Ref.matrix + 0) + 0) = 5;
  *(*(Ref.matrix + 0) + 1) = 4;
  *(*(Ref.matrix + 0) + 2) = 3;

  *(*(Ref.matrix + 1) + 0) = 8;
  *(*(Ref.matrix + 1) + 1) = 9;
  *(*(Ref.matrix + 1) + 2) = 5;

  *(*(Ref.matrix + 2) + 0) = 6;
  *(*(Ref.matrix + 2) + 1) = 5;
  *(*(Ref.matrix + 2) + 2) = 3;

  *(*(Ref.matrix + 3) + 0) = 11;
  *(*(Ref.matrix + 3) + 1) = 9;
  *(*(Ref.matrix + 3) + 2) = 6;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(mult_matrix_test2) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(4, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), 0);

  *(*(A.matrix + 0) + 0) = NAN;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_test3) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(4, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), 0);

  *(*(B.matrix + 0) + 0) = INFINITY;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_test4) {
  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, NULL), 1);
}
END_TEST

START_TEST(mult_matrix_test5) {
  matrix_t A, B, C;
  ck_assert_int_eq(s21_create_matrix(5, 5, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 5, &B), 0);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_test6) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(4, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), 0);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_test7) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(4, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), 0);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, NULL), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_mult_matrix(void) {
  Suite *s = suite_create("suite_mult_matrix");
  TCase *tc = tcase_create("mult_matrix_tc");

  tcase_add_test(tc, mult_matrix_test1);
  tcase_add_test(tc, mult_matrix_test2);
  tcase_add_test(tc, mult_matrix_test3);
  tcase_add_test(tc, mult_matrix_test4);
  tcase_add_test(tc, mult_matrix_test5);
  tcase_add_test(tc, mult_matrix_test6);
  tcase_add_test(tc, mult_matrix_test7);

  suite_add_tcase(s, tc);
  return s;
}