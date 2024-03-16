#include "test.h"

int main(void) {
  int failed = 0;
  Suite *s21_string_test[] = {test_24_func(),
                              test_sprintf_c(),
                              test_sprintf_e(),
                              test_sprintf_f(),
                              test_sprintf_g(),
                              test_sprintf_o(),
                              test_sprintf_percent(),
                              test_sprintf_n(),
                              test_sprintf_s(),
                              test_sprintf_u(),
                              test_sprintf_x(),
                              test_sprintf_p(),
                              test_sprintf_d(),
                              test_sprintf_i(),

                              test_scanf_i(),
                              test_scanf_c(),
                              test_scanf_s(),
                              test_scanf_p(),
                              test_scanf_n(),
                              test_scanf_d(),
                              test_scanf_u(),
                              test_scanf_o(),
                              test_scanf_x(),
                              test_scanf_f(),
                              test_scanf_weird(),

                              NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_string_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);
  return failed == 0 ? 0 : 1;
}
