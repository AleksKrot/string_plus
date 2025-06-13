#include "s21_string_test.h"

START_TEST(s21_sprintf_basic_test) {
    char buffer[50];
    char buffer_2[50];
    const char *str = "Hello, 50%%, %-5n%% World! ";
    char arg = 'c';
    s21_sprintf(buffer, str, arg);
    sprintf(buffer_2, str, arg);
    //ck_assert_int_eq(result, result_2);
    //ck_assert_str_eq(buffer, buffer_2);
    printf("\n");
    printf("%s", buffer);
    printf("\n");
    printf("%s", buffer_2);
    printf("\n");
}
END_TEST

Suite *s21_sprintf_suite(void) {
    Suite *s = suite_create("s21_sprintf");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_sprintf_basic_test);

    suite_add_tcase(s, tc);
    
    return s;
}