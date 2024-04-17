#include "test.h"

START_TEST(sprintf_d_1) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_2) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = INT_MIN;
  char *format = "|%d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_3) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = INT_MAX;
  char *format = "|%+d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_4) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = INT_MAX;
  char *format = "|% d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_5) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 0;
  char *format = "|%+d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_6) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 5346457;
  char *format = "|%015d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_7) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 6878;
  char *format = "|%1d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_8) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = -315;
  char *format = "|%4d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_9) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = -14566;
  char *format = "|%.1d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_10) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 56368;
  char *format = "|%.10d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_11) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = -67567;
  char *format = "|%.6d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_12) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 99999;
  char *format = "|%015.10d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_13) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = -131135;
  int y = 12;
  char *format = "|%.*d|\n";
  s21_sprintf(str1, format, y, x);
  sprintf(str2, format, y, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_14) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 354634;
  int y = 12;
  int z = 16;
  char *format = "|%*.*d|\n";
  s21_sprintf(str1, format, z, y, x);
  sprintf(str2, format, z, y, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_15) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 354634;
  int y = 12;
  int z = 16;
  char *format = "|%-*.*d|\n";
  s21_sprintf(str1, format, z, y, x);
  sprintf(str2, format, z, y, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_16) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 354634;
  char *format = "|%+-020.15d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_17) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 354634;
  char *format = "|%+-015.20d|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_1) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 12345678;
  char *format = "|%+-015.20i|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_o_1) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 12345678;
  char *format = "|%o|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_o_2) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 12345678;
  char *format = "|%+-15.20o|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_o_3) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 12345678;
  char *format = "|%#o|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_o_4) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 12345678;
  char *format = "|%#+-15.9o|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_sprintf_d_suite(void) {
  Suite *suite = suite_create("s21_sprintf_d_test");
  TCase *tcase_core = tcase_create("s21_sprintf_d_test");

  tcase_add_test(tcase_core, sprintf_d_1);
  tcase_add_test(tcase_core, sprintf_d_2);
  tcase_add_test(tcase_core, sprintf_d_3);
  tcase_add_test(tcase_core, sprintf_d_4);
  tcase_add_test(tcase_core, sprintf_d_5);
  tcase_add_test(tcase_core, sprintf_d_6);
  tcase_add_test(tcase_core, sprintf_d_7);
  tcase_add_test(tcase_core, sprintf_d_8);
  tcase_add_test(tcase_core, sprintf_d_9);
  tcase_add_test(tcase_core, sprintf_d_10);
  tcase_add_test(tcase_core, sprintf_d_11);
  tcase_add_test(tcase_core, sprintf_d_12);
  tcase_add_test(tcase_core, sprintf_d_13);
  tcase_add_test(tcase_core, sprintf_d_14);
  tcase_add_test(tcase_core, sprintf_d_15);
  tcase_add_test(tcase_core, sprintf_d_16);
  tcase_add_test(tcase_core, sprintf_d_17);
  tcase_add_test(tcase_core, sprintf_i_1);
  tcase_add_test(tcase_core, sprintf_o_1);
  tcase_add_test(tcase_core, sprintf_o_2);
  tcase_add_test(tcase_core, sprintf_o_3);
  tcase_add_test(tcase_core, sprintf_o_4);
  suite_add_tcase(suite, tcase_core);
  return suite;
}