#include "test.h"

START_TEST(strlen_1) {

  const char str[] = "This is a test string";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_2) {
  const char str[] = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_3) {
  const char str[] = "\0\0\0";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_4) {
  const char str[] = "1234567890";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_5) {
  const char str[] = "??$#@!@*";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_6) {
  const char str[] = "This is test\0 string";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_7) {
  const char *str = NULL;
  ck_assert_int_eq(s21_strlen(str), 0);
}
END_TEST

Suite *s21_strlen_suite(void) {
  Suite *suite = suite_create("s21_strlen_test");
  TCase *tcase_core = tcase_create("s21_strlen_test");

  tcase_add_test(tcase_core, strlen_1);
  tcase_add_test(tcase_core, strlen_2);
  tcase_add_test(tcase_core, strlen_3);
  tcase_add_test(tcase_core, strlen_4);
  tcase_add_test(tcase_core, strlen_5);
  tcase_add_test(tcase_core, strlen_6);
  tcase_add_test(tcase_core, strlen_7);

  suite_add_tcase(suite, tcase_core);
  return suite;
}