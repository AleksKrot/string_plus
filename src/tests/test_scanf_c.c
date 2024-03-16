#include "test.h"

START_TEST(testing_c1) {  // basic
  char str[] = "c";
  char format[] = "%c";
  char c1 = 0, c2 = 0;
  int16_t res1 = s21_sscanf(str, format, &c1);
  int16_t res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(testing_c2) {  // multiple
  char str[] = "c y u";
  char format[] = "%c%c%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c3) {  // multiple with spaces in format
  char str[] = "c y u";
  char format[] = "%c %c %c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c4) {  // multiple with spaces and tabs in format
  char str[] = "c y u";
  char format[] = "%c\n %c \t\n %c ";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c5) {  // multiple with asterisk
  char str[] = "c y u";
  char format[] = "%c %*c %c q";
  char c11 = 0, c12 = 0, c21 = 0, c22 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12);
  int16_t res2 = sscanf(str, format, &c21, &c22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
}
END_TEST

START_TEST(testing_c6) {  // multiple with spaces + asterisk in format
  char str[] = "c y u";
  char format[] = "%c\n %*c \t\n %c ";
  char c11 = 0, c12 = 0, c21 = 0, c22 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12);
  int16_t res2 = sscanf(str, format, &c21, &c22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
}
END_TEST

START_TEST(testing_c7) {  // long
  char str[] = "\t \t";
  char format[] = "%c%*c";
  char c1 = 0, c2 = 0;
  int16_t res1 = s21_sscanf(str, format, &c1);
  int16_t res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(testing_c8) {  // no percent?
  char str[] = "\t \tf";
  char format[] = "c %c";
  char c1 = 0, c2 = 0;
  int16_t res1 = s21_sscanf(str, format, &c1);
  int16_t res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(testing_c9) {
  char str[] = " cyu";
  char format[] = "  %c%c%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c10) {
  char str[] = "cyu";
  char format[] = "%c %c %c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c11) {
  char str[] = "c  y  u";
  char format[] = "%c%c%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c12) {
  char str[] = "c:y:u";
  char format[] = "%c:%c:%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c13) {
  char str[] = "c:y:u";
  char format[] = "%c::%c:%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c14) {
  char str[] = "     ";
  char format[] = "%c%c%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c15) {
  char str[] = "";
  char format[] = "%c%c%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c16) {
  char str[] = "a b c";
  char format[] = "%cc%c%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c17) {
  char str[] = "a b c";
  char format[] = "%1c %c %c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c18) {
  char str[] = "A B";
  char format[] = "%lc %lc";
  wchar_t a_w = 0;
  wchar_t b_w = 0;
  wchar_t c_w = 0;
  wchar_t d_w = 0;
  int16_t res1 = s21_sscanf(str, format, &a_w, &b_w);
  int16_t res2 = sscanf(str, format, &c_w, &d_w);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a_w, c_w);
  ck_assert_int_eq(b_w, d_w);
}
END_TEST

START_TEST(testing_c19) {
  char str[] = "  a b c ";
  char format[] = "  %c %%c%c";
  char c11 = 0, c12 = 0, c13 = 0, c21 = 0, c22 = 0, c23 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(testing_c20) {
  char str[] = " ";
  char format[] = " %c";
  char c11 = 0, c12 = 0;
  int16_t res1 = s21_sscanf(str, format, &c11);
  int16_t res2 = sscanf(str, format, &c12);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c12);
}
END_TEST

Suite *test_scanf_c(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_C=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_c1);
  tcase_add_test(tc, testing_c2);
  tcase_add_test(tc, testing_c3);
  tcase_add_test(tc, testing_c4);
  tcase_add_test(tc, testing_c5);
  tcase_add_test(tc, testing_c6);
  tcase_add_test(tc, testing_c7);
  tcase_add_test(tc, testing_c8);
  tcase_add_test(tc, testing_c9);
  tcase_add_test(tc, testing_c10);
  tcase_add_test(tc, testing_c11);
  tcase_add_test(tc, testing_c12);
  tcase_add_test(tc, testing_c13);
  tcase_add_test(tc, testing_c14);
  tcase_add_test(tc, testing_c15);
  tcase_add_test(tc, testing_c16);
  tcase_add_test(tc, testing_c17);
  tcase_add_test(tc, testing_c18);
  tcase_add_test(tc, testing_c19);
  tcase_add_test(tc, testing_c20);
  suite_add_tcase(s, tc);
  return s;
}
