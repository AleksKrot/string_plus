#include "test.h"

START_TEST(testing_f1) {  // basic
  char format[] = "%f";
  char str[] = "34.5";
  float f1, f2;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(testing_f2) {  // no percent
  char format[] = "f";
  char str[] = "34.5";
  float f1 = 0, f2 = 0;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(testing_f3) {  // double
  char format[] = "%lf";
  char str[] = "34.5";
  double f1, f2;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(f1, f2);
}
END_TEST

START_TEST(testing_f4) {  // empty
  char format[] = "%lf";
  char str[] = "";
  double f1 = 0, f2 = 0;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(f1, f2);
}
END_TEST

START_TEST(testing_f5) {  // long double
  char format[] = "%Lf";
  char str[] = "34.5";
  long double f1, f2;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(f1, f2);
}
END_TEST

START_TEST(testing_f6) {  // asterisk + inf nan e
  char format[] = "%*f %Lf %Lg %Le";
  char str[] = "inf nan +1e-7 -12e+2";
  long double f1, f2, e11 = 0, e21 = 0, e12 = 0, e22 = 0;
  int res1 = s21_sscanf(str, format, &f1, &e11, &e12);
  int res2 = sscanf(str, format, &f2, &e21, &e22);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_nan(f1);
  ck_assert_ldouble_eq(e11, e21);
  ck_assert_ldouble_eq(e12, e22);
}
END_TEST

START_TEST(testing_f7) {
  char format[] = "Lg";
  char str[] = "+1e-7 -12e+2";
  long double e11 = 0, e21 = 0;
  int res1 = s21_sscanf(str, format, &e11);
  int res2 = sscanf(str, format, &e21);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(e11, e21);
}
END_TEST

START_TEST(testing_f8) {
  char format[] = "LE";
  char str[] = "+1e-7 -12e+2";
  long double e11 = 0, e21 = 0;
  int res1 = s21_sscanf(str, format, &e11);
  int res2 = sscanf(str, format, &e21);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(e11, e21);
}
END_TEST

START_TEST(testing_f9) {  // long double error
  char format[] = "%Lf";
  char str[] = "-qqq";
  long double f1 = 0, f2 = 0;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(f1, f2);
}
END_TEST

START_TEST(testing_f10) {  // long double error
  char format[] = "%Lf";
  char str[] = "-+1.2";
  long double f1 = 0, f2 = 0;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(f1, f2);
}
END_TEST

START_TEST(testing_f11) {  // long double error
  char format[] = "%*f%f";
  char str[] = "1.2";
  long double f1 = 0, f2 = 0, f3 = 0, f4 = 0;
  int res1 = s21_sscanf(str, format, &f1, &f3);
  int res2 = sscanf(str, format, &f2, &f4);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(f1, f2);
}
END_TEST

START_TEST(testing_f12) {  // long double error
  char format[] = "%f";
  char str[] = "-1.2e-";
  long double f1 = 0, f2 = 0;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(f1, f2);
}
END_TEST

START_TEST(testing_f13) {  // long double error
  char format[] = "%3f";
  char str[] = "-1.2e1";
  long double f1 = 0, f2 = 0;
  int res1 = s21_sscanf(str, format, &f1);
  int res2 = sscanf(str, format, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(f1, f2);
}
END_TEST

Suite *test_scanf_f(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_F=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_f1);
  tcase_add_test(tc, testing_f2);
  tcase_add_test(tc, testing_f3);
  tcase_add_test(tc, testing_f4);
  tcase_add_test(tc, testing_f5);
  tcase_add_test(tc, testing_f6);
  tcase_add_test(tc, testing_f7);
  tcase_add_test(tc, testing_f8);
  tcase_add_test(tc, testing_f9);
  tcase_add_test(tc, testing_f10);
  tcase_add_test(tc, testing_f11);
  tcase_add_test(tc, testing_f12);
  tcase_add_test(tc, testing_f13);
  suite_add_tcase(s, tc);
  return s;
}
