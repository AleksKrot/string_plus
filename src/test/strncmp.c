#include "test.h"

START_TEST(strncmp_1) {

  const char str1[] = "This is a test string";
  const char str2[] = "This is a test string";
  ck_assert_int_eq(s21_strncmp(str1, str2, s21_strlen(str1)),
                   strncmp(str1, str2, s21_strlen(str1)));
}
END_TEST

START_TEST(strncmp_2) {

  const char str1[] = "";
  const char str2[] = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, s21_strlen(str1)),
                   strncmp(str1, str2, s21_strlen(str1)));
}
END_TEST

START_TEST(strncmp_3) {

  const char str1[] = "0123456789";
  const char str2[] = "0123789";
  ck_assert_int_eq(s21_strncmp(str1, str2, 4), strncmp(str1, str2, 4));
}
END_TEST

START_TEST(strncmp_4) {

  const char str1[] = "0123456789";
  const char str2[] = "0123789";
  ck_assert_int_eq(s21_strncmp(str1, str2, s21_strlen(str1)),
                   strncmp(str1, str2, s21_strlen(str1)));
}
END_TEST

START_TEST(strncmp_5) {

  const char str1[] = "school 21";
  const char str2[] = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
}
END_TEST

START_TEST(strncmp_6) {

  const char str1[] = "Hello";
  const char str2[] = "school 21";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
}
END_TEST

START_TEST(strncmp_7) {
  const char str1[] = "";
  const char str2[] = "school 21";
  ck_assert_int_eq(s21_strncmp(str1, str2, 15), strncmp(str1, str2, 15));
}
END_TEST

START_TEST(strncmp_8) {
  const char str1[] = "Hello";
  const char str2[] = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
}
END_TEST

START_TEST(strncmp_9) {
  const char str1[] = "Hello";
  const char str2[] = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
}
END_TEST

START_TEST(strncmp_10) {
  const char str1[] = "6368457857979094678478";
  const char str2[] = "1242345384594503486734";
  ck_assert_int_eq(s21_strncmp(str1, str2, 256), strncmp(str1, str2, 256));
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *suite = suite_create("s21_strncmp_test");
  TCase *tcase_core = tcase_create("s21_strncmp_test");

  tcase_add_test(tcase_core, strncmp_1);
  tcase_add_test(tcase_core, strncmp_2);
  tcase_add_test(tcase_core, strncmp_3);
  tcase_add_test(tcase_core, strncmp_4);
  tcase_add_test(tcase_core, strncmp_5);
  tcase_add_test(tcase_core, strncmp_6);
  tcase_add_test(tcase_core, strncmp_7);
  tcase_add_test(tcase_core, strncmp_8);
  tcase_add_test(tcase_core, strncmp_9);
  tcase_add_test(tcase_core, strncmp_10);

  suite_add_tcase(suite, tcase_core);
  return suite;
}