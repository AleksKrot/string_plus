#include "s21_string_test.h"

// Поиск символа в начале строки
START_TEST(s21_strpbrk_basic_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "Hello";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_str_eq(result, strpbrk(s1, s2));
}
END_TEST

// Совпадение в середине строки
START_TEST(s21_strpbrk_middle_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = ", W";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_str_eq(result, strpbrk(s1, s2));
}
END_TEST

// Совпадение в конце строки
START_TEST(s21_strpbrk_end_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "!";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_str_eq(result, strpbrk(s1, s2));
}
END_TEST

// Нет совпадения
START_TEST(s21_strpbrk_not_found_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "xyz";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_ptr_null(result);
}
END_TEST

// Пустая строка str1
START_TEST(s21_strpbrk_empty_str1_test) {
    const char *s1 = "";
    const char *s2 = "abc";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_ptr_null(result);
}
END_TEST

// Пустая строка str2
START_TEST(s21_strpbrk_empty_str2_test) {
    const char *s1 = "Hello";
    const char *s2 = "";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_ptr_null(result);
}
END_TEST

// Обе строки пустые
START_TEST(s21_strpbrk_empty_test) {
    const char *s1 = "";
    const char *s2 = "";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_ptr_null(result);
}
END_TEST

// Тест с несколькими совпадающими символами
START_TEST(s21_strpbrk_multiple_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "l";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_str_eq(result, strpbrk(s1, s2));
}
END_TEST

// Тест с нуль-терминатором
START_TEST(s21_strpbrk_zero_test) {
    const char *s1 = "Hello,\0 World!";
    const char *s2 = "ld";
    char *result = s21_strpbrk(s1, s2);
    ck_assert_ptr_eq(result, strpbrk(s1, s2));
    ck_assert_str_eq(result, strpbrk(s1, s2));
}
END_TEST

Suite *s21_strpbrk_suite(void) {
    Suite *s = suite_create("s21_strpbrk");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strpbrk_basic_test);
    tcase_add_test(tc, s21_strpbrk_middle_test);
    tcase_add_test(tc, s21_strpbrk_end_test);
    tcase_add_test(tc, s21_strpbrk_not_found_test);
    tcase_add_test(tc, s21_strpbrk_empty_str1_test);
    tcase_add_test(tc, s21_strpbrk_empty_str2_test);
    tcase_add_test(tc, s21_strpbrk_empty_test);
    tcase_add_test(tc, s21_strpbrk_multiple_test);
    tcase_add_test(tc, s21_strpbrk_zero_test);

    suite_add_tcase(s, tc);

    return s;
}