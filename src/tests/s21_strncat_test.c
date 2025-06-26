#include <check.h>

#include "../s21_string.h"

#define BUFFER_SIZE 256


// Объявление тестируемой функции
char *s21_strncat(char *dest, const char *src, s21_size_t n);
// Вспомогательная функция для сравнения строк
static int compare_strings(const char *s1, const char *s2);
Suite *memset_suite(void);

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = memset_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// Тестовые случаи
START_TEST(test_strncat_full) { // Добавление всей строки src в dest
    char dest[BUFFER_SIZE] = "Hello";
    const char *src = ", World!";
    s21_size_t n = strlen(src);

    char expected[BUFFER_SIZE];
    strcpy(expected, dest);
    strncat(expected, src, n);

    s21_strncat(dest, src, n);
    ck_assert_int_eq(compare_strings(dest, expected), 0);
}
END_TEST

START_TEST(test_strncat_partial) {
    char dest[BUFFER_SIZE] = "Hello";
    const char *src = ", World!";
    s21_size_t n = 3; // Добавляем только ", W"

    char expected[BUFFER_SIZE];
    strcpy(expected, dest);
    strncat(expected, src, n);

    s21_strncat(dest, src, n);
    ck_assert_int_eq(compare_strings(dest, expected), 0);
}
END_TEST



static int compare_strings(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}