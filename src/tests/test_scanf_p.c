#include "test.h"

START_TEST(testing_p1) {  // pointer basic
  char str[] = "0xabcd";
  char format[] = "%p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p2) {  // pointer no percent
  char str[] = "0xabcd";
  char format[] = "p %p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p3) {  // asterisk
  char str[] = "0xabcD 0x0000Aa";
  char format[] = "%*p %p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p4) {
  char str[] = "0xAAAA";
  char format[] = "%2p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p5) {
  char str[] = "0xAAA543A";
  char format[] = "%5p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p6) {
  char str[] = "0xFFFFFFFFFFFF";
  char format[] = "%p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p7) {
  char str[] = "0x0000";
  char format[] = "%p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p8) {
  char str[] = "A2361598";
  char format[] = "%p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p9) {
  char str[] = "0x23a7B48c";
  char format[] = "%100p";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_p10) {
  char str[] = "123";
  char format[] = "%*d%p";
  int n1 = 0, n2 = 0;
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1, &p1);
  int16_t res2 = sscanf(str, format, &n2, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

Suite *test_scanf_p(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_P=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_p1);
  tcase_add_test(tc, testing_p2);
  tcase_add_test(tc, testing_p3);
  tcase_add_test(tc, testing_p4);
  tcase_add_test(tc, testing_p5);
  tcase_add_test(tc, testing_p6);
  tcase_add_test(tc, testing_p7);
  tcase_add_test(tc, testing_p8);
  tcase_add_test(tc, testing_p9);
  tcase_add_test(tc, testing_p10);
  suite_add_tcase(s, tc);
  return s;
}
