#include "test.h"

START_TEST(testing_d1) {  // basic
  char format[] = "%d";
  char str[] = "11";
  int d1, d2;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_d2) {  // multiple
  char format[] = "%d %d";
  char str[] = "11 22";
  int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d3) {  // multiple with asterisk
  char format[] = "%d %*d %d";
  char str[] = "11 22 33";
  int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d4) {  // ends incorrect
  char format[] = "%d";
  char str[] = "11q";
  int d1, d2;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_d5) {  // multiple + starts incorrect
  char format[] = "%d %d";
  char str[] = "11 q22";
  int d11, d12 = 0, d21, d22 = 0;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d6) {  // multiple with asterisk + ends incorrect
  char format[] = "%d %*d %d";
  char str[] = "11 22 33q";
  int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d7) {  // signed
  char format[] = "%hhd %*hhd %hhd";
  char str[] = "11 22 33";
  signed char d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d8) {  // short
  char format[] = "%hd %*hd %hd";
  char str[] = "11 22 33q";
  short int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d9) {  // long
  char format[] = "%ld %*ld %ld";
  char str[] = "11 22 33q";
  long int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d10) {  // long long + plus sign
  char format[] = "%lld %*lld %lld";
  char str[] = "11 +22 -33q";
  long long int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d11, d21);
  ck_assert_int_eq(d12, d22);
}
END_TEST

START_TEST(testing_d11) {  // percent
  char format[] = "%%ld";
  char str[] = "11 22 33q";
  long int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_d12) {  // no percent
  char format[] = "d";
  char str[] = "%11 %22 33q";
  int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_d13) {  // precision
  char format[] = "%4d";
  char str[] = "11 22 33q";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_d14) {  // number bigger than precision + minus sign
  char format[] = "%4d";
  char str[] = "-11123123123123";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_d15) {  // empty
  char format[] = "%d";
  char str[] = "/t";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_d16) {  // real empty
  char format[] = "%d";
  char str[] = "";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_d17) {  // real empty
  char format[] = "%*d%d";
  char str[] = "123";
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
}
END_TEST

START_TEST(testing_d18) {
  char format[] = "%hd %hd %hd %hd";
  char str[] =
      "-9223372036854775808 -9223372036854775808 9223372036854775807 "
      "9223372036854775808";
  short int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  short int d5 = 0, d6 = 0, d7 = 0, d8 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d2, &d3, &d4);
  int16_t res2 = sscanf(str, format, &d5, &d6, &d7, &d8);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d5);
  ck_assert_int_eq(d2, d6);
  ck_assert_int_eq(d3, d7);
  ck_assert_int_eq(d4, d8);
}
END_TEST

START_TEST(testing_d19) {
  char format[] = "%d %d %d %d";
  char str[] =
      "-9223372036854775808 -9223372036854775808 9223372036854775807 "
      "9223372036854775808";
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int d5 = 0, d6 = 0, d7 = 0, d8 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d2, &d3, &d4);
  int16_t res2 = sscanf(str, format, &d5, &d6, &d7, &d8);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d5);
  ck_assert_int_eq(d2, d6);
  ck_assert_int_eq(d3, d7);
  ck_assert_int_eq(d4, d8);
}
END_TEST

START_TEST(testing_d20) {
  char format[] = "%ld %ld %ld %ld";
  char str[] =
      "-9223372036854775808 -9223372036854775808 9223372036854775807 "
      "9223372036854775808";
  long int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  long int d5 = 0, d6 = 0, d7 = 0, d8 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d2, &d3, &d4);
  int16_t res2 = sscanf(str, format, &d5, &d6, &d7, &d8);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d5);
  ck_assert_int_eq(d2, d6);
  ck_assert_int_eq(d3, d7);
  ck_assert_int_eq(d4, d8);
}
END_TEST

START_TEST(testing_d21) {
  char format[] = "%lld %lld %lld %lld";
  char str[] =
      "-9223372036854775808 -9223372036854775808 9223372036854775807 "
      "9223372036854775808";
  long long int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  long long int d5 = 0, d6 = 0, d7 = 0, d8 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d2, &d3, &d4);
  int16_t res2 = sscanf(str, format, &d5, &d6, &d7, &d8);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d5);
  ck_assert_int_eq(d2, d6);
  ck_assert_int_eq(d3, d7);
  ck_assert_int_eq(d4, d8);
}
END_TEST

Suite *test_scanf_d(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_D=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_d1);
  tcase_add_test(tc, testing_d2);
  tcase_add_test(tc, testing_d3);
  tcase_add_test(tc, testing_d4);
  tcase_add_test(tc, testing_d5);
  tcase_add_test(tc, testing_d6);
  tcase_add_test(tc, testing_d7);
  tcase_add_test(tc, testing_d8);
  tcase_add_test(tc, testing_d9);
  tcase_add_test(tc, testing_d10);
  tcase_add_test(tc, testing_d11);
  tcase_add_test(tc, testing_d12);
  tcase_add_test(tc, testing_d13);
  tcase_add_test(tc, testing_d14);
  tcase_add_test(tc, testing_d15);
  tcase_add_test(tc, testing_d16);
  tcase_add_test(tc, testing_d17);
  tcase_add_test(tc, testing_d18);
  tcase_add_test(tc, testing_d19);
  tcase_add_test(tc, testing_d20);
  tcase_add_test(tc, testing_d21);
  suite_add_tcase(s, tc);
  return s;
}
