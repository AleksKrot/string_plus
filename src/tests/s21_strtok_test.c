#include "s21_string_test.h"

// Базовый случай
START_TEST(s21_strtok_basic_test) {
    char s1[] = " !Hello, World!";
    char s2[] = " !Hello, World!";
    const char *d = " ,!";
    char *result = s21_strtok(s1, d);
    ck_assert_pstr_eq(result, strtok(s2, d));

    result = s21_strtok(S21_NULL, d);
    ck_assert_pstr_eq(result, strtok(S21_NULL, d));
}
END_TEST

// Делитель отсутствует
START_TEST(s21_strtok_null_delim_test) {
    char s1[] = "Hello, World!";
    char s2[] = "Hello, World!";
    const char *d = "";
    char *result = s21_strtok(s1, d);
    ck_assert_pstr_eq(result, strtok(s2, d));

    result = s21_strtok(S21_NULL, d);
    ck_assert_pstr_eq(result, strtok(S21_NULL, d));
}
END_TEST

// Строка пустая
START_TEST(s21_strtok_null_str_test) {
    char s1[] = "";
    char s2[] = "";
    const char *d = " ,!";
    char *result = s21_strtok(s1, d);
    ck_assert_pstr_eq(result, strtok(s2, d));

    result = s21_strtok(S21_NULL, d);
    ck_assert_pstr_eq(result, strtok(S21_NULL, d));
}
END_TEST

// Строка пустая и делитель отсутствует
START_TEST(s21_strtok_null_both_test) {
    char s1[] = "";
    char s2[] = "";
    const char *d = "";
    char *result = s21_strtok(s1, d);
    ck_assert_pstr_eq(result, strtok(s2, d));

    result = s21_strtok(S21_NULL, d);
    ck_assert_pstr_eq(result, strtok(S21_NULL, d));
}
END_TEST

Suite *s21_strtok_suite(void) {
    Suite *s = suite_create("s21_strtok");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strtok_basic_test);
    tcase_add_test(tc, s21_strtok_null_delim_test);
    tcase_add_test(tc, s21_strtok_null_str_test);
    tcase_add_test(tc, s21_strtok_null_both_test);

    suite_add_tcase(s, tc);

    return s;
}