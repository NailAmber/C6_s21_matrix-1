#include <check.h>

#include "s21_matrix_test.h"

START_TEST(calc_complements_test1) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(1, 1, &A), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &Ref), 0);

  *(*(A.matrix + 0) + 0) = -64;

  *(*(Ref.matrix + 0) + 0) = -64;

  ck_assert_int_eq(s21_calc_complements(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(calc_complements_test2) {}
END_TEST

START_TEST(calc_complements_test3) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(4, 4, &A), 0);
  ck_assert_int_eq(s21_create_matrix(4, 4, &Ref), 0);

  *(*(A.matrix + 0) + 0) = 1;
  *(*(A.matrix + 0) + 1) = 0;
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

  *(*(Ref.matrix + 0) + 0) = -54;
  *(*(Ref.matrix + 0) + 1) = -12;
  *(*(Ref.matrix + 0) + 2) = 12;
  *(*(Ref.matrix + 0) + 3) = 3;

  *(*(Ref.matrix + 1) + 0) = -18;
  *(*(Ref.matrix + 1) + 1) = -4;
  *(*(Ref.matrix + 1) + 2) = 4;
  *(*(Ref.matrix + 1) + 3) = 1;

  *(*(Ref.matrix + 2) + 0) = 0;
  *(*(Ref.matrix + 2) + 1) = 0;
  *(*(Ref.matrix + 2) + 2) = 0;
  *(*(Ref.matrix + 2) + 3) = 0;

  *(*(Ref.matrix + 3) + 0) = 36;
  *(*(Ref.matrix + 3) + 1) = 8;
  *(*(Ref.matrix + 3) + 2) = -8;
  *(*(Ref.matrix + 3) + 3) = -2;

  ck_assert_int_eq(s21_calc_complements(&A, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(calc_complements_test4) {
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), 1);
}
END_TEST

START_TEST(calc_complements_test5) {
  matrix_t A;
  ck_assert_int_eq(s21_calc_complements(&A, NULL), 1);
}
END_TEST

START_TEST(calc_complements_test6) {
  matrix_t A, B;
  s21_create_matrix(4, 3, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &B), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_test_zero_row) {}
END_TEST

START_TEST(calc_complements_test_singular_matrix) {}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("calc_complements_tc");

  tcase_add_test(tc, calc_complements_test1);
  tcase_add_test(tc, calc_complements_test2);
  tcase_add_test(tc, calc_complements_test3);
  tcase_add_test(tc, calc_complements_test4);
  tcase_add_test(tc, calc_complements_test5);
  tcase_add_test(tc, calc_complements_test6);
  tcase_add_test(tc, calc_complements_test_zero_row);
  tcase_add_test(tc, calc_complements_test_singular_matrix);

  suite_add_tcase(s, tc);
  return s;
}