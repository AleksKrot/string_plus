#include <check.h>
#include <string.h>

#include "s21_string_function.h"

START_TEST(s21_memchr_basic_test) {
  const char *str = "Hello, World!";
  char c = 'o';
  s21_size_t n = 14;
  void *result = s21_memchr(str, c, n);
  ck_assert_ptr_nonnull(result);
  ck_assert_ptr_eq(result, memchr(str, c, strlen(str)));
}
END_TEST

START_TEST(s21_memchr_absence_test) {
  const char *str = "Hello, World!";
  char c = 'B';
  s21_size_t n = 14;
  void *result = s21_memchr(str, c, n);
  ck_assert_ptr_null(result);
  ck_assert_ptr_eq(result, memchr(str, c, strlen(str)));
}
END_TEST

START_TEST(s21_memchr_double_test) {
  const char *str = "Hello, World!";
  char c = 'l';
  s21_size_t n = 14;
  void *result = s21_memchr(str, c, n);
  ck_assert_ptr_nonnull(result);
  ck_assert_ptr_eq(result, memchr(str, c, strlen(str)));
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

int main(void) {
  int number_failed;
  int result;
  Suite *s = s21_memchr_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  if (number_failed == 0) {
    result = EXIT_SUCCESS;
  } else {
    result = EXIT_FAILURE;
  }
  return result;
}