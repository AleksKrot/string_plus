#include "s21_string_test.h"

// Совпадение в начале строки
START_TEST(s21_strcspn_basic_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "Hello, Krot!";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

// Совпадение в середине строки
START_TEST(s21_strcspn_middle_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = ",";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

// Совпадение в конце строки
START_TEST(s21_strcspn_end_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "!";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

// Нет совпадения
START_TEST(s21_strcspn_not_found_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "xyz";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

// Пустая строка str1
START_TEST(s21_strcspn_empty_str1_test) {
    const char *s1 = "";
    const char *s2 = "abc";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

// Пустая строка str2
START_TEST(s21_strcspn_empty_str2_test) {
    const char *s1 = "Hello";
    const char *s2 = "";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

// Обе строки пустые
START_TEST(s21_strcspn_empty_test) {
    const char *s1 = "";
    const char *s2 = "";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

// Тест с несколькими совпадающими символами
START_TEST(s21_strcspn_multiple_test) {
    const char *s1 = "Hello, World!";
    const char *s2 = "ol";
    s21_size_t result = s21_strcspn(s1, s2);
    ck_assert_int_eq(result, strcspn(s1, s2));
}
END_TEST

Suite *s21_strcspn_suite(void) {
    Suite *s = suite_create("s21_strcspn");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strcspn_basic_test);
    tcase_add_test(tc, s21_strcspn_middle_test);
    tcase_add_test(tc, s21_strcspn_end_test);
    tcase_add_test(tc, s21_strcspn_not_found_test);
    tcase_add_test(tc, s21_strcspn_empty_str1_test);
    tcase_add_test(tc, s21_strcspn_empty_str2_test);
    tcase_add_test(tc, s21_strcspn_empty_test);
    tcase_add_test(tc, s21_strcspn_multiple_test);

    suite_add_tcase(s, tc);

    return s;
}