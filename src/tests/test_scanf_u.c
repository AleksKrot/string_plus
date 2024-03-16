#include "test.h"

START_TEST(testing_u1) {  // basic
  char format[] = "%u";
  char str[] = "11";
  unsigned int d1, d2;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_u2) {  // multiple
  char format[] = "%u %u";
  char str[] = "11 22";
  unsigned int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u3) {  // multiple with asterisk
  char format[] = "%u %*u %u";
  char str[] = "11 22 33";
  unsigned int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u4) {  // ends incorrect
  char format[] = "%u";
  char str[] = "11q";
  unsigned int d1, d2;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_u5) {  // multiple + starts incorrect
  char format[] = "%d %d";
  char str[] = "11 q22";
  unsigned int d11, d12 = 0, d21, d22 = 0;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u6) {  // multiple with asterisk + ends incorrect
  char format[] = "%u %*u %u";
  char str[] = "11 22 33q";
  unsigned int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u7) {  // signed
  char format[] = "%hhu %*hhu %hhu";
  char str[] = "11 22 33";
  unsigned char d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u8) {  // short
  char format[] = "%hu %*hu %hu";
  char str[] = "11 22 33q";
  unsigned short int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u9) {  // long
  char format[] = "%lu %*lu %lu";
  char str[] = "11 22 33q";
  unsigned long int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u10) {  // long long + plus sign
  char format[] = "%llu %*llu %llu";
  char str[] = "11 +22 -33q";
  unsigned long long int d11, d12, d21, d22;
  int16_t res1 = s21_sscanf(str, format, &d11, &d12);
  int16_t res2 = sscanf(str, format, &d21, &d22);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d11, d21);
  ck_assert_uint_eq(d12, d22);
}
END_TEST

START_TEST(testing_u11) {  // percent
  char format[] = "%%lu";
  char str[] = "11 22 33q";
  unsigned long int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(n1, n2);
}
END_TEST

START_TEST(testing_u12) {  // no percent
  char format[] = "u";
  char str[] = "%11 %22 33q";
  unsigned int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(n1, n2);
}
END_TEST

START_TEST(testing_u13) {  // precision
  char format[] = "%4u";
  char str[] = "11 22 33q";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_u14) {  // number bigger than precision + minus sign
  char format[] = "%4u";
  char str[] = "-11123123123123";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_u15) {  // empty
  char format[] = "%u";
  char str[] = "/t";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_u16) {  // real empty
  char format[] = "%u";
  char str[] = "";
  unsigned int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(testing_u17) {  // real empty
  char format[] = "%*u%u";
  char str[] = "123";
  unsigned int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &d3);
  int16_t res2 = sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(d3, d4);
}
END_TEST

Suite *test_scanf_u(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_U=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_u1);
  tcase_add_test(tc, testing_u2);
  tcase_add_test(tc, testing_u3);
  tcase_add_test(tc, testing_u4);
  tcase_add_test(tc, testing_u5);
  tcase_add_test(tc, testing_u6);
  tcase_add_test(tc, testing_u7);
  tcase_add_test(tc, testing_u8);
  tcase_add_test(tc, testing_u9);
  tcase_add_test(tc, testing_u10);
  tcase_add_test(tc, testing_u11);
  tcase_add_test(tc, testing_u12);
  tcase_add_test(tc, testing_u13);
  tcase_add_test(tc, testing_u14);
  tcase_add_test(tc, testing_u15);
  tcase_add_test(tc, testing_u16);
  tcase_add_test(tc, testing_u17);
  suite_add_tcase(s, tc);
  return s;
}
