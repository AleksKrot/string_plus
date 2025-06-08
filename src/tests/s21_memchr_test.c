#include "s21_string.h"

#include <check.h>
#include <string.h>

// Символ найден
START_TEST(s21_memchr_basic_test) {
    const char *str = "Hello, World!";
    char c = 'o';
    s21_size_t n = s21_strlen(str);
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

// Символ, который находится на границе n
START_TEST(s21_memchr_border_test) {
    const char *str = "Hello, World!";
    char c = 'o';
    s21_size_t n = 5;
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

// Поиск символа, который встречается несколько раз
START_TEST(s21_memchr_double_test) {
    const char *str = "Hello, World!";
    char c = 'l';
    s21_size_t n = s21_strlen(str);
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

// Символ не найден
START_TEST(s21_memchr_absence_test) {
    const char *str = "Hello, World!";
    char c = 'B';
    s21_size_t n = s21_strlen(str);
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_null(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

// Пустая строка
START_TEST(s21_memchr_empty_test) {
    const char *str = "";
    char c = 'a';
    s21_size_t n = s21_strlen(str);
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_null(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

// Поиск нуль-терминатор
START_TEST(s21_memchr_null_test) {
    const char *str = "Hello\0World!";
    char c = '\0';
    s21_size_t n = s21_strlen(str);
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_null(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

// Cимвол есть, но за пределами n
START_TEST(s21_memchr_limited_test) {
    const char *str = "Hello, World!";
    char c = 'W';
    s21_size_t n = 5;
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_null(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

Suite *s21_memchr_suite(void) {
    Suite *s = suite_create("s21_memchr");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_memchr_basic_test);
    tcase_add_test(tc, s21_memchr_border_test);
    tcase_add_test(tc, s21_memchr_double_test);
    tcase_add_test(tc, s21_memchr_absence_test);
    tcase_add_test(tc, s21_memchr_empty_test);
    tcase_add_test(tc, s21_memchr_null_test);
    tcase_add_test(tc, s21_memchr_limited_test);
    suite_add_tcase(s, tc);
    
    return s;
}