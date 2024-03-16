#include "test.h"

START_TEST(testing_weird_1) {
  char format[] = "%";
  char str[] = "342432";
  unsigned short int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_weird_2) {
  char format[] = "% ";
  char str[] = "342432";
  unsigned short int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_weird_3) {
  char format[] = "%lo";
  char str[] = " ";
  unsigned long int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_weird_4) {
  char format[] = "%lf";
  char str[] = " ";
  double d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(testing_weird_5) {
  char format[] = "qqqq";
  char str[] = "qqqq";
  char d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_weird_6) {
  char format[] = "%p";
  char str[] = " ";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(testing_weird_7) {
  char format[] = "        %	%%%%%%\tlo";
  char str[] = "        %342";
  unsigned long int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_weird_8) {
  char format[] = "%n";
  char str[] = "";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(testing_weird_9) {
  char format[] = "%%d";
  char str[] = ":";
  int d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

Suite *test_scanf_weird(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_WEIRD=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_weird_1);
  tcase_add_test(tc, testing_weird_2);
  tcase_add_test(tc, testing_weird_3);
  tcase_add_test(tc, testing_weird_4);
  tcase_add_test(tc, testing_weird_5);
  tcase_add_test(tc, testing_weird_6);
  tcase_add_test(tc, testing_weird_7);
  tcase_add_test(tc, testing_weird_8);
  tcase_add_test(tc, testing_weird_9);
  suite_add_tcase(s, tc);

  return s;
}
