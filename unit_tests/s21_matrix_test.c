#include "s21_matrix_test.h"

void run_tests(void) {
  Suite *list_cases[] = {
      suite_create_matrix(),    suite_remove_matrix(),  suite_eq_matrix(),
      suite_sum_matrix(),       suite_sub_matrix(),     suite_mult_number(),
      suite_mult_matrix(),      suite_transpose(),      suite_determinant(),
      suite_calc_complements(), suite_inverse_matrix(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_tests();
  return 0;
}