#include "s21_matrix_test.h"

START_TEST(remove_matrix_test1) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(remove_matrix_test2) { s21_remove_matrix(&(matrix_t){NULL, 1, 0}); }
END_TEST

START_TEST(remove_matrix_test3) { s21_remove_matrix(&(matrix_t){NULL, 0, 1}); }
END_TEST

START_TEST(remove_matrix_test4) { s21_remove_matrix(NULL); }
END_TEST

Suite *suite_remove_matrix(void) {
  Suite *s = suite_create("suite_remove_matrix");
  TCase *tc = tcase_create("remove_matrix_tc");

  tcase_add_test(tc, remove_matrix_test1);
  tcase_add_test(tc, remove_matrix_test2);
  tcase_add_test(tc, remove_matrix_test3);
  tcase_add_test(tc, remove_matrix_test4);

  suite_add_tcase(s, tc);
  return s;
}