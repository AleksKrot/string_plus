#include "s21_string_test.h"

// Объединение строк
START_TEST(s21_strncat_basic_test) {
    char dest1[20] = "Hello, ";
    char dest2[20] = "Hello, ";
    const char *s = "World!";
    s21_size_t n = 6;
    char *result = s21_strncat(dest1, s, n);
    ck_assert_ptr_eq(result, dest1);
    ck_assert_ptr_eq(strncat(dest2, s, n), dest2);
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

// Объединение с ограничением длины
START_TEST(s21_strncat_partical_test) {
    char dest1[20] = "Hello, ";
    char dest2[20] = "Hello, ";
    const char *s = "World!";
    s21_size_t n = 2;
    char *result = s21_strncat(dest1, s, n);
    ck_assert_ptr_eq(result, dest1);
    ck_assert_ptr_eq(strncat(dest2, s, n), dest2);
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

// Объединение с n = 0
START_TEST(s21_strncat_zero_n_test) {
    char dest1[20] = "Hello, ";
    char dest2[20] = "Hello, ";
    const char *s = "World!";
    s21_size_t n = 0;
    char *result = s21_strncat(dest1, s, n);
    ck_assert_ptr_eq(result, dest1);
    ck_assert_ptr_eq(strncat(dest2, s, n), dest2);
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

Suite *s21_strncat_suite(void) {
    Suite *s = suite_create("s21_memset");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strncat_basic_test);
    tcase_add_test(tc, s21_strncat_partical_test);
    tcase_add_test(tc, s21_strncat_zero_n_test);

    suite_add_tcase(s, tc);
    
    return s;
}