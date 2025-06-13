#include "s21_string_test.h"

// Заполнение всего буфера
START_TEST(s21_strchr_basic_test) {
    const char *s = "Hello, World!";
    char c = 'H';
    char *result = s21_strchr(s, c);
    ck_assert_ptr_eq(result, strchr(s, c));
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, c);
}
END_TEST

Suite *s21_strchr_suite(void) {
    Suite *s = suite_create("s21_strchr");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_strchr_basic_test);
    //tcase_add_test(tc, s21_memset_non_zero_test);
    //tcase_add_test(tc, s21_memset_full_buffer_test);

    suite_add_tcase(s, tc);
    
    return s;
}