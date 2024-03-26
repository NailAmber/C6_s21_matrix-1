#include "s21_matrix_test.h"

START_TEST(mult_number_test1) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
  ck_assert_int_eq(s21_mult_number(&A, 500.473, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_number_test2) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &Ref), 0);
  fill_matrix(&A);
  ck_assert_int_eq(s21_mult_number(&A, 0, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(mult_number_test3) {
  matrix_t A, B, Ref;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &Ref), 0);
  fill_matrix(&A);

  *(*(Ref.matrix + 0) + 1) = 151.1093342;
  *(*(Ref.matrix + 0) + 2) = 302.2186684;

  *(*(Ref.matrix + 1) + 0) = 453.3280026;
  *(*(Ref.matrix + 1) + 1) = 604.4373368;
  *(*(Ref.matrix + 1) + 2) = 755.546671;

  *(*(Ref.matrix + 2) + 0) = 906.6560052;
  *(*(Ref.matrix + 2) + 1) = 1057.7653394;
  *(*(Ref.matrix + 2) + 2) = 1208.8746736;

  ck_assert_int_eq(s21_mult_number(&A, 137.372122, &B), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &Ref), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Ref);
}
END_TEST

START_TEST(mult_number_test4) {
  ck_assert_int_eq(s21_mult_number(NULL, 2, NULL), 1);
}
END_TEST

START_TEST(mult_number_test5) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
  ck_assert_int_eq(s21_mult_number(&A, NAN, &B), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_test6) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
  ck_assert_int_eq(s21_mult_number(&A, 2, NULL), 1);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_mult_number(void) {
  Suite *s = suite_create("suite_mult_number");
  TCase *tc = tcase_create("mult_number_tc");

  tcase_add_test(tc, mult_number_test1);
  tcase_add_test(tc, mult_number_test2);
  tcase_add_test(tc, mult_number_test3);
  tcase_add_test(tc, mult_number_test4);
  tcase_add_test(tc, mult_number_test5);
  tcase_add_test(tc, mult_number_test6);

  suite_add_tcase(s, tc);
  return s;
}