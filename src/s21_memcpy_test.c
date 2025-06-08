#include "s21_string_function.h"

#include <check.h>
#include <string.h>
#include <stdio.h>

START_TEST(s21_memcpy_basic_test) {
    const char *s = "Hello, World!";
    s21_size_t n = s21_strlen(s);
    char d[n];
    void *result = s21_memcpy(d, s, n);
    ck_assert_ptr_eq(result, memcpy(d, s, n));
    ck_assert_mem_eq(d, s, n);
}
END_TEST

Suite *s21_memcpy_suite(void) {
    Suite *s = suite_create("s21_memcpy");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_memcpy_basic_test);

    suite_add_tcase(s, tc);
    
    return s;
}