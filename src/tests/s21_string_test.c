#include "s21_string_test.h"

int main(void) {
    int number_failed;
    int result;

    Suite *(*test_suites[])() = {
//        s21_memchr_suite,
//        s21_memcmp_suite,
//        s21_memcpy_suite,
//        s21_memset_suite,
//        s21_strncat_suite,
//        s21_strchr_suite,
//        s21_sprintf_suite,
//        s21_strrchr_suite,
//        s21_strncmp_suite,
//        s21_strncpy_suite,
//        s21_strcspn_suite,
//        s21_strlen_suite,
//        s21_strpbrk_suite,
//        s21_strstr_suite,
        s21_strtok_suite,
        S21_NULL
    };

    SRunner *sr = srunner_create(S21_NULL);
    
    for (int i = 0; *(test_suites + i) != S21_NULL; i++) {
        Suite *s = test_suites[i]();
        srunner_add_suite(sr, s);
    }
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (number_failed == 0) {
        result = EXIT_SUCCESS;
    } else {
        result = EXIT_FAILURE;
    }
    return result;
}