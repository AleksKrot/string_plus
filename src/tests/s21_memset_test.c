#include "s21_string_test.h"

// Заполнение нулями
START_TEST(s21_memset_basic_test) {
    char s1[20] = "Hello, World!";
    char s2[20] = "Hello, World!";
    s21_size_t n = s21_strlen(s1);
    char c = '0';
    char *result = s21_memset(s1, c, n);
    ck_assert_ptr_eq(result, s1);
    ck_assert_ptr_eq(memset(s2, c, n), s2);
    ck_assert_mem_eq(s1, s2, n);
}
END_TEST

// Заполнение не нулевыми значениями
START_TEST(s21_memset_non_zero_test) {
    char s1[20] = {0};
    char s2[20] = {0};
    char c = 'F';
    char *result = s21_memset(s1, c, 5);
    ck_assert_ptr_eq(result, s1);
    ck_assert_ptr_eq(memset(s2, c, 5), s2);
    ck_assert_mem_eq(s1, s2, 20);
}
END_TEST

// Заполнение всего буфера
START_TEST(s21_memset_full_buffer_test) {
    char s1[14] = "Hello, World!";
    char s2[14] = "Hello, World!";
    char c = 'Z';
    char *result = s21_memset(s1, c, 14);
    ck_assert_ptr_eq(result, s1);
    ck_assert_ptr_eq(memset(s2, c, 14), s2);
    ck_assert_mem_eq(s1, s2, 14);
}
END_TEST

Suite *s21_memset_suite(void) {
    Suite *s = suite_create("s21_memset");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_memset_basic_test);
    tcase_add_test(tc, s21_memset_non_zero_test);
    tcase_add_test(tc, s21_memset_full_buffer_test);

    suite_add_tcase(s, tc);
    
    return s;
}