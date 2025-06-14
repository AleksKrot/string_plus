#include "s21_string_test.h"

// Базовый тест
START_TEST(s21_strlen_basic_test) {
    const char *s1 = "Hello, World!";
    s21_size_t result = s21_strlen(s1);
    ck_assert_int_eq(result, strlen(s1));
}
END_TEST

// Пустая строка
START_TEST(s21_strlen_empty_test) {
    const char *s1 = "";
    s21_size_t result = s21_strlen(s1);
    ck_assert_int_eq(result, strlen(s1));
}
END_TEST

// Длинная строка
START_TEST(s21_strlen_long_test) {
    const char *s1 = "This is a very long string with multiple words and symbols @#$%^&*()";
    s21_size_t result = s21_strlen(s1);
    ck_assert_int_eq(result, strlen(s1));
}
END_TEST

// Один символ
START_TEST(s21_strlen_one_test) {
    const char *s1 = "T";
    s21_size_t result = s21_strlen(s1);
    ck_assert_int_eq(result, strlen(s1));
}
END_TEST

// Нуль-терминатор
START_TEST(s21_strlen_zero_test) {
    const char *s1 = "Hello,\0 World!";
    s21_size_t result = s21_strlen(s1);
    ck_assert_int_eq(result, strlen(s1));
}
END_TEST

// Строка из пробелов
START_TEST(s21_strlen_space_test) {
    const char *s1 = "         ";
    s21_size_t result = s21_strlen(s1);
    ck_assert_int_eq(result, strlen(s1));
}
END_TEST

Suite *s21_strlen_suite(void) {
    Suite *s = suite_create("s21_strlen");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strlen_basic_test);
    tcase_add_test(tc, s21_strlen_empty_test);
    tcase_add_test(tc, s21_strlen_long_test);
    tcase_add_test(tc, s21_strlen_one_test);
    tcase_add_test(tc, s21_strlen_zero_test);
    tcase_add_test(tc, s21_strlen_space_test);

    suite_add_tcase(s, tc);

    return s;
}