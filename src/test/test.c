#include "test.h"

int main() {
  run_tests();
  return 0;
}

void run_testcase(Suite *testscase, int counter_testcase) {
  if (counter_testcase > 1)
    putchar('\n');
  printf("Test %d:\n", counter_testcase);

  SRunner *sr = srunner_create(testscase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
}
void run_tests() {
  int counter_testcase = 0;
  Suite *list_cases[] = {s21_memchr_suite(),
                         s21_strlen_suite(),
                         s21_memcmp_suite(),
                         s21_memset_suite(),
                         s21_memcpy_suite(),
                         s21_strncat_suite(),
                         s21_strchr_suite(),
                         s21_strncmp_suite(),
                         s21_strncpy_suite(),
                         s21_sprintf_suite(),
                         NULL};

  for (Suite **testcase = list_cases; *testcase; testcase++) {
    run_testcase(*testcase, ++counter_testcase);
  }
}