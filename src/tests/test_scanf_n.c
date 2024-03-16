#include "test.h"

START_TEST(testing_n1) {
  char format[] = "%n";
  char str[] = "inf";
  int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_n2) {
  char format[] = "%d %n";
  char str[] = "1231 inf";
  int d1, d2, n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1, &n1);
  int16_t res2 = sscanf(str, format, &d2, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_n3) {
  char format[] = "%n";
  char str[] = "           \n   inf";
  int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_n4) {
  char format[] = "%d %n";
  char str[] = "123 456";
  int n1 = 0, n2 = 0;
  int n3 = 0, n4 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1, &n2);
  int16_t res2 = sscanf(str, format, &n3, &n4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n3);
  ck_assert_int_eq(n2, n4);
}
END_TEST

START_TEST(testing_n5) {
  char format[] = "%d %*n";
  char str[] = "123 456";
  int n1 = 0, n2 = 0;
  int n3 = 0, n4 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1, &n2);
  int16_t res2 = sscanf(str, format, &n3, &n4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n3);
  ck_assert_int_eq(n2, n4);
}
END_TEST

START_TEST(testing_n6) {
  char format[] = "%d %hhn %d %hn %d %n %d %ln %d %lln";
  char str[] = "1 22 3  4  45 6  7 8 9   0";
  int n11 = 0, n12 = 0, n13 = 0, n14 = 0, n15 = 0, n16 = 0, n17 = 0, n18 = 0,
      n19 = 0, n10 = 0;
  int n21 = 0, n22 = 0, n23 = 0, n24 = 0, n25 = 0, n26 = 0, n27 = 0, n28 = 0,
      n29 = 0, n20 = 0;
  int16_t res1 = s21_sscanf(str, format, &n11, &n12, &n13, &n14, &n15, &n16,
                            &n17, &n18, &n19, &n10);
  int16_t res2 = sscanf(str, format, &n21, &n22, &n23, &n24, &n25, &n26, &n27,
                        &n28, &n29, &n20);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n11, n21);
  ck_assert_int_eq(n12, n22);
  ck_assert_int_eq(n13, n23);
  ck_assert_int_eq(n14, n24);
  ck_assert_int_eq(n15, n25);
  ck_assert_int_eq(n16, n26);
  ck_assert_int_eq(n17, n27);
  ck_assert_int_eq(n18, n28);
  ck_assert_int_eq(n19, n29);
  ck_assert_int_eq(n10, n20);
}
END_TEST

START_TEST(testing_n7) {
  char format[] = " %n";
  char str[] = "        ";
  int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_n8) {
  char format[] = " %%n";
  char str[] = "      dw";
  int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(testing_n9) {
  char format[] = "n";
  char str[] = "      f";
  int n1 = 0, n2 = 0;
  int16_t res1 = s21_sscanf(str, format, &n1);
  int16_t res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *test_scanf_n(void) {
  Suite *s = suite_create("\033[45m-=S21_SCANF_N=-\033[0m");
  TCase *tc = tcase_create("scanf_tc");
  tcase_add_test(tc, testing_n1);
  tcase_add_test(tc, testing_n2);
  tcase_add_test(tc, testing_n3);
  tcase_add_test(tc, testing_n4);
  tcase_add_test(tc, testing_n5);
  tcase_add_test(tc, testing_n6);
  tcase_add_test(tc, testing_n7);
  tcase_add_test(tc, testing_n8);
  tcase_add_test(tc, testing_n9);
  suite_add_tcase(s, tc);
  return s;
}
