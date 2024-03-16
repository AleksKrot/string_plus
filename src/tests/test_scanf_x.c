#include "test.h"

START_TEST(testing_x1) {  // pointer basic
  char str[] = "0xabcd";
  char format[] = "%x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x2) {  // pointer no percent
  char str[] = "0xabcd";
  char format[] = "x %x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x3) {  // asterisk
  char str[] = "0xabcD 0x0000Aa";
  char format[] = "%*x %x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x4) {
  char str[] = "0xAAAA";
  char format[] = "%2x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x5) {
  char str[] = "0xAAA543A";
  char format[] = "%5x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x6) {
  char str[] = "0xFFFFFFFFFFFF";
  char format[] = "%x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x7) {
  char str[] = "0x0000";
  char format[] = "%x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x8) {
  char str[] = "A2361598";
  char format[] = "%x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x9) {
  char str[] = "0x23a7B48c";
  char format[] = "%100x";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_x10) {
  char str[] = "123";
  char format[] = "%*d%x";
  int n1 = 0, n2 = 0;
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1, &p1);
  int16_t res2 = sscanf(str, format, &n2, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

Suite *test_scanf_x(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_X=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_x1);
  tcase_add_test(tc, testing_x2);
  tcase_add_test(tc, testing_x3);
  tcase_add_test(tc, testing_x4);
  tcase_add_test(tc, testing_x5);
  tcase_add_test(tc, testing_x6);
  tcase_add_test(tc, testing_x7);
  tcase_add_test(tc, testing_x8);
  tcase_add_test(tc, testing_x9);
  tcase_add_test(tc, testing_x10);
  suite_add_tcase(s, tc);
  return s;
}
