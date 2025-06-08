#include "s21_string_function.h"
#include "s21_sprintf.h"

#include <check.h>
#include <string.h>
#include <stdio.h>

START_TEST(s21_sprintf_basic_test) {
    char buffer[50]; // TODO Динамическая память
    const char *str = "Hello, 50%%, %c World!";
    char arg = 'c';
    int result = s21_sprintf(buffer, str, arg);
    ck_assert_int_eq(result, sprintf(buffer, str, arg));
    ck_assert_str_eq(buffer, str);
}
END_TEST

Suite *s21_sprintf_suite(void) {
    Suite *s = suite_create("s21_sprintf");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_sprintf_basic_test);

    suite_add_tcase(s, tc);
    
    return s;
}