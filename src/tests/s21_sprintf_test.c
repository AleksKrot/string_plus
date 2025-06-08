#include "s21_string.h"
#include "s21_sprintf.h"

#include <check.h>
#include <string.h>
#include <stdio.h>

START_TEST(s21_sprintf_basic_test) {
    char buffer[50]; // TODO Динамическая память
    char buffer_2[50];
    const char *str = "Hello, 50%%, %-+ 3c World!";
    char arg = 'c';
    int result = s21_sprintf(buffer, str, arg);
    ck_assert_int_eq(result, sprintf(buffer_2, str, arg));
    ck_assert_str_eq(buffer, buffer_2);
    printf("\n");
    printf("%s", buffer);
    printf("\n");
    printf("%s", buffer_2);
    printf("\n");
}
END_TEST

Suite *s21_sprintf_suite(void) {
    Suite *s = suite_create("s21_sprintf");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_sprintf_basic_test);

    suite_add_tcase(s, tc);
    
    return s;
}