#include "s21_string_test.h"

// Копирование всей строки
START_TEST(s21_strncpy_basic_test) {
    const char *s = "Hello, World!";
    s21_size_t n = s21_strlen(s);
    char d[n];
    void *result = s21_strncpy(d, s, n);
    ck_assert_ptr_eq(result, strncpy(d, s, n));
    ck_assert_str_eq(result, strncpy(d, s, n));
}
END_TEST

// Копирование части строки
START_TEST(s21_strncpy_partial_test) {
    const char *s = "Hello, World!";
    s21_size_t n = 5;
    char d[n];
    void *result = s21_strncpy(d, s, n);
    ck_assert_ptr_eq(result, strncpy(d, s, n));
    ck_assert_str_eq(result, strncpy(d, s, n));
}
END_TEST

// Копирование нулевого размера
START_TEST(s21_strncpy_zero_size_test) {
    const char *s = "Hello, World!";
    s21_size_t n = 0;
    char d[n];
    void *result = s21_strncpy(d, s, n);
    ck_assert_ptr_eq(result, strncpy(d, s, n));
    ck_assert_str_eq(result, strncpy(d, s, n));
}
END_TEST

// Копирование большего размера
START_TEST(s21_strncpy_over_size_test) {
    const char *s = "Hello, World!";
    s21_size_t n = s21_strlen(s) + 2;
    char d[n];
    void *result = s21_strncpy(d, s, n);
    ck_assert_ptr_eq(result, strncpy(d, s, n));
    ck_assert_str_eq(result, strncpy(d, s, n));
}
END_TEST

Suite *s21_strncpy_suite(void) {
    Suite *s = suite_create("s21_strncpy");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strncpy_basic_test);
    tcase_add_test(tc, s21_strncpy_partial_test);
    tcase_add_test(tc, s21_strncpy_zero_size_test);
    tcase_add_test(tc, s21_strncpy_over_size_test);

    suite_add_tcase(s, tc);

    return s;
}