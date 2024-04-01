#include "test.h"

START_TEST(strncpy_1) {

  char str1[] = "This is a test string";
  char str1_copy[] = "This is a test string";
  const char str2[] = "This is a test string";

  s21_strncpy(str1, str2, s21_strlen(str1));
  strncpy(str1_copy, str2, s21_strlen(str1));
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_2) {

  char str1[] = "This is a test string";
  char str1_copy[] = "This is a test string";
  const char str2[] = "";

  s21_strncpy(str1, str2, s21_strlen(str2));
  strncpy(str1_copy, str2, s21_strlen(str2));
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_3) {

  char str1[256];
  char str1_copy[256];
  const char str2[] = "This is a test string";

  s21_strncpy(str1, str2, s21_strlen(str2));
  strncpy(str1_copy, str2, s21_strlen(str2));
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_4) {
  char str1[] = "This is a test string";
  char str1_copy[] = "This is a test string";
  const char str2[] = "This is a test string ";

  s21_strncpy(str1, str2, 1);
  strncpy(str1_copy, str2, 1);
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_5) {

  char str1[] = "123456789";
  char str1_copy[] = "123456789";
  const char str2[] = "abcdef";

  s21_strncpy(str1, str2, 3);
  strncpy(str1_copy, str2, 3);
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_6) {

  char str1[] = "123456789";
  char str1_copy[] = "123456789";
  const char str2[] = "abcdef";

  s21_strncpy(str1, str2, s21_strlen(str2));
  strncpy(str1_copy, str2, s21_strlen(str2));
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_7) {

  const char str1[] = "This is a test string";
  char str2[] = "test";
  char str2_copy[] = "test";

  s21_strncpy(str2, str1, s21_strlen(str2));
  strncpy(str2_copy, str1, s21_strlen(str2));
  ck_assert_str_eq(str2, str2_copy);
}
END_TEST

START_TEST(strncpy_8) {

  char str1[] = "\0\0\0";
  char str1_copy[] = "\0\0\0";
  const char str2[] = "\0";

  s21_strncpy(str1, str2, 1);
  strncpy(str1, str2, 1);
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_9) {

  char str1[] = "Hello, world!";
  char str1_copy[] = "Hello, world!";
  const char str2[] = "test";

  s21_strncpy(str1, str2, 1);
  strncpy(str1_copy, str2, 1);
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

START_TEST(strncpy_10) {
  char str1[] = "This is a test string";
  char str1_copy[] = "This is a test string";
  const char str2[] = "test";

  s21_strncpy((str1 + 10), str2, strlen(str2));
  strncpy((str1_copy + 10), str2, strlen(str2));
  ck_assert_str_eq(str1, str1_copy);
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *suite = suite_create("s21_strncpy_test");
  TCase *tcase_core = tcase_create("s21_strncpy_test");

  tcase_add_test(tcase_core, strncpy_1);
  tcase_add_test(tcase_core, strncpy_2);
  tcase_add_test(tcase_core, strncpy_3);
  tcase_add_test(tcase_core, strncpy_4);
  tcase_add_test(tcase_core, strncpy_5);
  tcase_add_test(tcase_core, strncpy_6);
  tcase_add_test(tcase_core, strncpy_7);
  tcase_add_test(tcase_core, strncpy_8);
  tcase_add_test(tcase_core, strncpy_9);
  tcase_add_test(tcase_core, strncpy_10);

  suite_add_tcase(suite, tcase_core);
  return suite;
}