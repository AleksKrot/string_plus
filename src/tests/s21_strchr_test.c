#include "s21_string_test.h"

// Поиск символа в начале строки
START_TEST(s21_strchr_basic_test) {
    const char *s = "Hello, World!";
    char c = 'H';
    char *result = s21_strchr(s, c);
    ck_assert_ptr_eq(result, strchr(s, c));
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, c);
}
END_TEST

// Поиск символа в середине строки
START_TEST(s21_strchr_middle_test) {
    const char *s = "Hello, World!";
    char c = 'l';
    char *result = s21_strchr(s, c);
    ck_assert_ptr_eq(result, strchr(s, c));
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, c);
}
END_TEST

// Поиск символа в конце строки
START_TEST(s21_strchr_end_test) {
    const char *s = "Hello, World!";
    char c = '!';
    char *result = s21_strchr(s, c);
    ck_assert_ptr_eq(result, strchr(s, c));
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, c);
}
END_TEST

// Поиск нуль-терминатора
START_TEST(s21_strchr_null_test) {
    const char *s = "Hello, World!";
    char c = '\0';
    char *result = s21_strchr(s, c);
    ck_assert_ptr_eq(result, strchr(s, c));
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, c);
}
END_TEST

// Поиск символа в пустой строке
START_TEST(s21_strchr_empty_test) {
    const char *s = "";
    char c = 'v';
    char *result = s21_strchr(s, c);
    ck_assert_ptr_eq(result, strchr(s, c));
    ck_assert_ptr_null(result);
}
END_TEST

// Поиск символа, которого нет в строке
START_TEST(s21_strchr_not_found_test) {
    const char *s = "Hello, World!";
    char c = 'v';
    char *result = s21_strchr(s, c);
    ck_assert_ptr_eq(result, strchr(s, c));
    ck_assert_ptr_null(result);
}
END_TEST

Suite *s21_strchr_suite(void) {
    Suite *s = suite_create("s21_strchr");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strchr_basic_test);
    tcase_add_test(tc, s21_strchr_middle_test);
    tcase_add_test(tc, s21_strchr_end_test);
    tcase_add_test(tc, s21_strchr_null_test);
    tcase_add_test(tc, s21_strchr_empty_test);
    tcase_add_test(tc, s21_strchr_not_found_test);

    suite_add_tcase(s, tc);
    
    return s;
}