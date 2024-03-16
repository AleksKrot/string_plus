#include "test.h"

START_TEST(testing_s1) {  // basic
  char str[] = "xabcd";
  char format[] = "%s";
  char s1[N] = "0", s2[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1);
  int16_t res2 = sscanf(str, format, s2);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(testing_s2) {  // no percent
  char str[] = "xabcd";
  char format[] = "s %s";
  char s1[N] = "0", s2[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1);
  int16_t res2 = sscanf(str, format, s2);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(testing_s3) {  // asterisk suppress
  char str[] = "string xabcd";
  char format[] = "%*s %s";
  char s1[N] = "0", s2[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1);
  int16_t res2 = sscanf(str, format, s2);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(testing_s4) {  // \0
  char str[] = "string \00xabcd";
  char format[] = "%s %s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s5) {
  char str[] = "         ldewewp";
  char format[] = "%s";
  char s1[N] = "0", s2[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1);
  int16_t res2 = sscanf(str, format, s2);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(testing_s6) {
  char str[] = "";
  char format[] = "%s %s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s7) {
  char str[] = "\n\n\n\n\t\t\t    \t\t\n";
  char format[] = "%s %s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s8) {
  char str[] = "abcdefgh";
  char format[] = "%2s %3s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s9) {
  char str[] = "abcdefgh";
  char format[] = "%100s %3s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s10) {
  char str[] = "abc defgh";
  char format[] = "%2s %3s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s11) {
  char str[] = "abc def gh";
  char format[] = "%2s %s %s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  char s5[N] = "0", s6[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2, s3);
  int16_t res2 = sscanf(str, format, s4, s5, s6);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s4);
  ck_assert_pstr_eq(s2, s5);
  ck_assert_pstr_eq(s3, s6);
}
END_TEST

START_TEST(testing_s12) {
  char str[] = "abc def";
  char format[] = "%*2s %3s %s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s13) {
  char str[] = "abc def";
  char format[] = "%ss %s";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(testing_s14) {
  char str[] = "abc def";
  char format[] = "%s %%%%%3s   ";
  char s1[N] = "0", s2[N] = "0";
  char s3[N] = "0", s4[N] = "0";
  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

Suite *test_scanf_s(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_S=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_s1);
  tcase_add_test(tc, testing_s2);
  tcase_add_test(tc, testing_s3);
  tcase_add_test(tc, testing_s4);
  tcase_add_test(tc, testing_s5);
  tcase_add_test(tc, testing_s6);
  tcase_add_test(tc, testing_s7);
  tcase_add_test(tc, testing_s8);
  tcase_add_test(tc, testing_s9);
  tcase_add_test(tc, testing_s10);
  tcase_add_test(tc, testing_s11);
  tcase_add_test(tc, testing_s12);
  tcase_add_test(tc, testing_s13);
  tcase_add_test(tc, testing_s14);
  suite_add_tcase(s, tc);
  return s;
}
