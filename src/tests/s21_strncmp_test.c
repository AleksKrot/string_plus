#include "s21_string_test.h"

// Одинаковые массивы
START_TEST(s21_strncmp_basic_test) {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    s21_size_t n = s21_strlen(str1);
    int result = s21_strncmp(str1, str2, n);
    ck_assert_int_eq(result, strncmp(str1, str2, n));
}
END_TEST

// Первый массив меньше
START_TEST(s21_strncmp_smaller_test) {
    const char *str1 = "Hello, Apple!";
    const char *str2 = "Hello, World!";
    s21_size_t n = 9;
    int result = s21_strncmp(str1, str2, n);
    ck_assert_int_eq(result, strncmp(str1, str2, n));
}
END_TEST

// Первый массив больше
START_TEST(s21_strncmp_bigger_test) {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, Krot!";
    s21_size_t n = 9;
    int result = s21_strncmp(str1, str2, n);
    ck_assert_int_eq(result, strncmp(str1, str2, n));
}
END_TEST

// Сравнение нулевого размера
START_TEST(s21_strncmp_zero_test) {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    s21_size_t n = 0;
    int result = s21_strncmp(str1, str2, n);
    ck_assert_int_eq(result, strncmp(str1, str2, n));
}
END_TEST

// Сравнение с нуль-терминатором
START_TEST(s21_strncmp_null_test) {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello,\0World!";
    s21_size_t n = s21_strlen(str1);
    int result = s21_strncmp(str1, str2, n);
    ck_assert_int_eq(result, strncmp(str1, str2, n));
}
END_TEST

Suite *s21_strncmp_suite(void) {
    Suite *s = suite_create("s21_strncmp");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strncmp_basic_test);
    tcase_add_test(tc, s21_strncmp_smaller_test);
    tcase_add_test(tc, s21_strncmp_bigger_test);
    tcase_add_test(tc, s21_strncmp_zero_test);
    tcase_add_test(tc, s21_strncmp_null_test);

    suite_add_tcase(s, tc);

    return s;
}