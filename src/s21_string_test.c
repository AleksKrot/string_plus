#include <check.h>
#include <string.h>

#define TEST_MEMCHR
#define TEST_MEMCMP
#define TEST_MEMCPY

#include "s21_string_function.h"
#include "s21_string_test.h"

int main(void) {
    int number_failed;
    int result;

    Suite *(*test_suites[])() = {
    #ifdef TEST_MEMCHR
        s21_memchr_suite,
    #endif

    #ifdef TEST_MEMCMP
        s21_memcmp_suite,
    #endif

    #ifdef TEST_MEMCPY
        s21_memcpy_suite,
    #endif
        NULL
    };

    SRunner *sr = srunner_create(NULL);
    
    for (int i = 0; *(test_suites + i) != NULL; i++) {
        Suite *s = test_suites[i]();
        srunner_add_suite(sr, s);
    }
    
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (number_failed == 0) {
        result = EXIT_SUCCESS;
    } else {
        result = EXIT_FAILURE;
    }
    return result;
}