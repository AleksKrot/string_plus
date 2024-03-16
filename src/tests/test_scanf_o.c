#include "test.h"

START_TEST(testing_o1) {  // basic
  char format[] = "%o";
  char str[] = "11";
  unsigned int d1, d2;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_o2) {  // multiple
  char format[] = "%o %o";
  char str[] = "11 22";
  unsigned int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o3) {  // multiple with asterisk
  char format[] = "%o %*o %o";
  char str[] = "11 22 33";
  unsigned int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o4) {  // ends incorrect
  char format[] = "%o";
  char str[] = "11q";
  unsigned int d1, d2;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_o5) {  // multiple + starts incorrect
  char format[] = "%o %o";
  char str[] = "11 q22";
  unsigned int d11, d12 = 0, d21, d22 = 0;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o6) {  // multiple with asterisk + ends incorrect
  char format[] = "%o %*o %o";
  char str[] = "11 22 33q";
  unsigned int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o7) {  // signed
  char format[] = "%hho %*hho %hho";
  char str[] = "11 22 33";
  unsigned char d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o8) {  // short
  char format[] = "%ho %*ho %ho";
  char str[] = "11 22 33q";
  unsigned short int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o9) {  // long
  char format[] = "%lo %*lo %lo";
  char str[] = "11 22 33q";
  unsigned long int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o10) {  // long long + plus sign
  char format[] = "%llo %*llo %llo";
  char str[] = "11 +22 -33q";
  unsigned long long int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_o11) {  // percent
  char format[] = "%%lo";
  char str[] = "11 22 33q";
  unsigned long int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(n1, n2);
}
END_TEST

START_TEST(testing_o12) {  // no percent
  char format[] = "o";
  char str[] = "%11 %22 33q";
  unsigned int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(n1, n2);
}
END_TEST

START_TEST(testing_o13) {  // precision
  char format[] = "%4o";
  char str[] = "11 22 33q";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_o14) {  // number bigger than precision + minus sign
  char format[] = "%4o";
  char str[] = "-11123123123123";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_o15) {  // empty
  char format[] = "%o";
  char str[] = "/t";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_o16) {  // real empty
  char format[] = "%o";
  char str[] = "";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_o17) {  // real empty
  char format[] = "%*o%o";
  char str[] = "123";
  unsigned int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(d3, d4);
}
END_TEST

Suite *test_scanf_o(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_O=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_o1);
  tcase_add_test(tc, testing_o2);
  tcase_add_test(tc, testing_o3);
  tcase_add_test(tc, testing_o4);
  tcase_add_test(tc, testing_o5);
  tcase_add_test(tc, testing_o6);
  tcase_add_test(tc, testing_o7);
  tcase_add_test(tc, testing_o8);
  tcase_add_test(tc, testing_o9);
  tcase_add_test(tc, testing_o10);
  tcase_add_test(tc, testing_o11);
  tcase_add_test(tc, testing_o12);
  tcase_add_test(tc, testing_o13);
  tcase_add_test(tc, testing_o14);
  tcase_add_test(tc, testing_o15);
  tcase_add_test(tc, testing_o16);
  tcase_add_test(tc, testing_o17);
  suite_add_tcase(s, tc);
  return s;
}
