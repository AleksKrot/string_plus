#include "test.h"

START_TEST(testing_i1) {  // basic dec
  char format[] = "%i";
  char str[] = "2876";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i2) {  // neg dec
  char format[] = "%i";
  char str[] = "-2876";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i3) {  // basic oct
  char format[] = "%i";
  char str[] = "0276";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i4) {  // neg oct
  char format[] = "%i";
  char str[] = "-0276";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i5) {  // basic hex
  char format[] = "%i";
  char str[] = "0x276";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i6) {  // neg hex
  char format[] = "%i";
  char str[] = "-0X276";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i7) {  // hex numbers
  char format[] = "%i";
  char str[] = "0X2757AFacnbhiuh";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i8) {  // oct invalid numbers
  char format[] = "%i";
  char str[] = "027876879";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i9) {  // no percent
  char format[] = "i";
  char str[] = "027876879";
  int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_i10) {  // lli max num
  char format[] = "%lli";
  char str[] = "27876879768768768768768768768768768768768768768769879877678798";
  long long int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i11) {  // precision
  char format[] = "%35i";
  char str[] = "000000x757CB657A";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i12) {
  char format[] = "%35i";
  char str[] = "7572387487236827638472";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_i13) {
  char format[] = "%li";
  char str[] = "0757237472123456235423321465";
  long int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_i14) {
  char format[] = "%li";
  char str[] = "-0757237472123456235423321465";
  long int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_i15) {
  char format[] = "%i";
  char str[] = "-0757237472123456235423321465";
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_i16) {
  char format[] = "%i";
  char str[] = "0757237472123456235423321465";
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_i17) {
  char format[] = "%li";
  char str[] = "0x757237472123456235423321465";
  long int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_i18) {
  char format[] = "%li";
  char str[] = "-0x757237472123456235423321465";
  long int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_i19) {
  char format[] = "%i";
  char str[] = "-0x757237472123456235423321465";
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_i20) {
  char format[] = "%i";
  char str[] = "0x757237472123456235423321465";
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

Suite *test_scanf_i(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_I=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_i1);
  tcase_add_test(tc, testing_i2);
  tcase_add_test(tc, testing_i3);
  tcase_add_test(tc, testing_i4);
  tcase_add_test(tc, testing_i5);
  tcase_add_test(tc, testing_i6);
  tcase_add_test(tc, testing_i7);
  tcase_add_test(tc, testing_i8);
  tcase_add_test(tc, testing_i9);
  tcase_add_test(tc, testing_i10);
  tcase_add_test(tc, testing_i11);
  tcase_add_test(tc, testing_i12);
  tcase_add_test(tc, testing_i13);
  tcase_add_test(tc, testing_i14);
  tcase_add_test(tc, testing_i15);
  tcase_add_test(tc, testing_i16);
  tcase_add_test(tc, testing_i17);
  tcase_add_test(tc, testing_i18);
  tcase_add_test(tc, testing_i19);
  tcase_add_test(tc, testing_i20);
  suite_add_tcase(s, tc);
  return s;
}
