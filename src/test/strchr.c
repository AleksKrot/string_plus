#include "test.h"

START_TEST(strchr_1) {

  const char str[] = "This is a test string";
  char c = 's';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_2) {

  const char str[] = "0123456789";
  char c = '5';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_3) {

  const char str[] = "Hello, world!";
  char c = 'z';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_4) {
  const char str[] = "This is a test string";
  char c = 's';

  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_5) {
  const char str[] = "\0";
  char c = 's';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_6) {
  const char str[] = "\0\0\0";
  char c = '\0';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_7) {
  const char str[] = "school 21";
  char c = ' ';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_8) {
  const char str[] = "\0school 21";
  char c = '1';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_9) {
  const char str[] = "Hello, world!";
  char c = ',';
  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

START_TEST(strchr_10) {
  const char str[] = "B\0AAAAAAAAAAAAAAAAAA!";
  char c = 'A';

  ck_assert_pstr_eq(s21_strchr(str, (int)c), strchr(str, (int)c));
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *suite = suite_create("s21_strchr_test");
  TCase *tcase_core = tcase_create("s21_strchr_test");

  tcase_add_test(tcase_core, strchr_1);
  tcase_add_test(tcase_core, strchr_2);
  tcase_add_test(tcase_core, strchr_3);
  tcase_add_test(tcase_core, strchr_4);
  tcase_add_test(tcase_core, strchr_5);
  tcase_add_test(tcase_core, strchr_6);
  tcase_add_test(tcase_core, strchr_7);
  tcase_add_test(tcase_core, strchr_8);
  tcase_add_test(tcase_core, strchr_9);
  tcase_add_test(tcase_core, strchr_10);

  suite_add_tcase(suite, tcase_core);
  return suite;
}