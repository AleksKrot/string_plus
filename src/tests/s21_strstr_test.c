#include "s21_string_test.h"

// Поиск подстроки в начале строки
START_TEST(s21_strstr_basic_test) {
    const char *h = "Hello, World!";
    const char *n = "Hello";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Поиск подстроки в середине строки
START_TEST(s21_strstr_midle_test) {
    const char *h = "Hello, World!";
    const char *n = "lo, W";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Поиск подстроки в конце строки
START_TEST(s21_strstr_end_test) {
    const char *h = "Hello, World!";
    const char *n = "!";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Поиск подстроки в строке с несколькими совпадениями
START_TEST(s21_strstr_multiple_test) {
    const char *h = "abababab";
    const char *n = "aba";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Поиск пустой подстроки в строке
START_TEST(s21_strstr_empty_needle_test) {
    const char *h = "Hello, world!";
    const char *n = "";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Поиск подстроки в пустой строке
START_TEST(s21_strstr_empty_haystack_test) {
    const char *h = "";
    const char *n = "world";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Нет подстроки в строке
START_TEST(s21_strstr_not_found_test) {
    const char *h = "Hello, world!";
    const char *n = "Krot";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Поиск пустой подстроки в пустой строке
START_TEST(s21_strstr_both_empty_test) {
    const char *h = "";
    const char *n = "";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

// Подстрока и строка идентичны
START_TEST(s21_strstr_equal_test) {
    const char *h = "Hello";
    const char *n = "Hello";
    char *result = s21_strstr(h, n);
    ck_assert_ptr_eq(result, strstr(h, n));
}
END_TEST

Suite *s21_strstr_suite(void) {
    Suite *s = suite_create("s21_strstr");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strstr_basic_test);
    tcase_add_test(tc, s21_strstr_midle_test);
    tcase_add_test(tc, s21_strstr_end_test);
    tcase_add_test(tc, s21_strstr_multiple_test);
    tcase_add_test(tc, s21_strstr_empty_needle_test);
    tcase_add_test(tc, s21_strstr_empty_haystack_test);
    tcase_add_test(tc, s21_strstr_not_found_test);
    tcase_add_test(tc, s21_strstr_both_empty_test);
    tcase_add_test(tc, s21_strstr_equal_test);

    suite_add_tcase(s, tc);

    return s;
}