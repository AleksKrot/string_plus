#ifndef S21_STRING_TEST_H  
#define S21_STRING_TEST_H

#ifdef TEST_MEMCHR //TODO добавить тесты memchr
START_TEST(s21_memchr_basic_test) {
    const char *str = "Hello, World!";
    char c = 'o';
    s21_size_t n = 14;
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

START_TEST(s21_memchr_absence_test) {
    const char *str = "Hello, World!";
    char c = 'B';
    s21_size_t n = 14;
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_null(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

START_TEST(s21_memchr_double_test) {
    const char *str = "Hello, World!";
    char c = 'l';
    s21_size_t n = 14;
    void *result = s21_memchr(str, c, n);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_eq(result, memchr(str, c, n));
}
END_TEST

Suite *s21_memchr_suite(void) {
    Suite *s = suite_create("s21_memchr");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_memchr_basic_test);
    tcase_add_test(tc, s21_memchr_absence_test);
    tcase_add_test(tc, s21_memchr_double_test);
    suite_add_tcase(s, tc);
    
    return s;
}
#endif

#ifdef TEST_MEMCMP //TODO добавить тесты memcmp
START_TEST(s21_memcmp_basic_test) {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    s21_size_t n = 14;
    int result = s21_memcmp(str1, str2, n);
    ck_assert_int_eq(result, memcmp(str1, str2, n));
}
END_TEST

Suite *s21_memcmp_suite(void) {
    Suite *s = suite_create("s21_memcmp");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_memcmp_basic_test);
    suite_add_tcase(s, tc);
    
    return s;
}
#endif

#ifdef TEST_MEMCPY //TODO добавить тесты memcpy
START_TEST(s21_memcpy_basic_test) {
    const char *s = "Hello, World!";
    s21_size_t n = 14;
    char d[n];
    void *result = s21_memcpy(d, s, n);
    ck_assert_ptr_eq(result, memcpy(d, s, n));
    ck_assert_mem_eq(d, s, n);
}
END_TEST

Suite *s21_memcpy_suite(void) {
    Suite *s = suite_create("s21_memcpy");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, s21_memcpy_basic_test);
    suite_add_tcase(s, tc);
    
    return s;
}
#endif

#endif