#include "s21_matrix_test.h"

START_TEST(create_matrix_test1) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(1, 2, &A), 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_test2) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(1, 0, &A), 1);
}
END_TEST

START_TEST(create_matrix_test3) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(0, 0, &A), 1);
}
END_TEST

START_TEST(create_matrix_test4) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(0, 1, &A), 1);
}
END_TEST

START_TEST(create_matrix_test5) {
  ck_assert_int_eq(s21_create_matrix(1, 1, NULL), 1);
}
END_TEST

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("suite_create_matrix");
  TCase *tc = tcase_create("create_matrix_tc");

  tcase_add_test(tc, create_matrix_test1);
  tcase_add_test(tc, create_matrix_test2);
  tcase_add_test(tc, create_matrix_test3);
  tcase_add_test(tc, create_matrix_test4);
  tcase_add_test(tc, create_matrix_test5);

  suite_add_tcase(s, tc);
  return s;
}