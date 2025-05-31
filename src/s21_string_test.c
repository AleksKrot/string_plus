#include "s21_string_function.h"
#include "s21_memchr_test.c"
#include "s21_memcmp_test.c"
#include "s21_memcpy_test.c"

int main(void) {
    int number_failed;
    int result;

    Suite *(*test_suites[])() = {
        s21_memchr_suite,
        s21_memcmp_suite,
        s21_memcpy_suite,
        NULL
    };

    SRunner *sr = srunner_create(NULL);
    
    for (int i = 0; *(test_suites + i) != NULL; i++) {
        Suite *s = test_suites[i]();
        srunner_add_suite(sr, s);
    }
    
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