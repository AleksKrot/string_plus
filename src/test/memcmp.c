#include "test.h"

int sign_int(int x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

START_TEST(memcmp_1) {

  const char str1[] = "This is a test string";
  const char str2[] = "This is a test string";
  int res1 =
      s21_memcmp((const void *)str1, (const void *)str2, s21_strlen(str1));
  int res2 = memcmp((const void *)str1, (const void *)str2, s21_strlen(str1));

  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_2) {

  const char str1[] = "";
  const char str2[] = "";
  int res1 = s21_memcmp(str1, str2, s21_strlen(str1));
  int res2 = memcmp(str1, str2, s21_strlen(str1));

  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_3) {

  const char str1[] = "0123456789";
  const char str2[] = "0123789";
  int res1 = s21_memcmp(str1, str2, 4);
  int res2 = memcmp(str1, str2, 4);

  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_4) {

  const char str1[] = "0123456789";
  const char str2[] = "0123789";
  int res1 = s21_memcmp(str1, str2, s21_strlen(str1));
  int res2 = memcmp(str1, str2, s21_strlen(str1));

  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_5) {

  const char str1[] = "school 21";
  const char str2[] = "Hello";
  int res1 = s21_memcmp(str1, str2, 1);
  int res2 = memcmp(str1, str2, 1);
  ck_assert_int_eq(sign_int(res1), sign_int(res2));
  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_6) {

  const char str1[] = "Hello";
  const char str2[] = "school 21";
  int res1 = s21_memcmp(str1, str2, 1);
  int res2 = memcmp(str1, str2, 1);

  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_7) {
  const char str1[] = "";
  const char str2[] = "school 21";
  int res1 = s21_memcmp(str1, str2, 15);
  int res2 = memcmp(str1, str2, 15);

  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_8) {
  const char str1[] = "Hello";
  const char str2[] = "";
  int res1 = s21_memcmp(str1, str2, 1);
  int res2 = memcmp(str1, str2, 1);
  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_9) {
  const char str1[] = "Hello";
  const char str2[] = "";
  int res1 = s21_memcmp(str1, str2, 1);
  int res2 = memcmp(str1, str2, 1);

  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_10) {
  const char str1[] = "6368457857979094678478";
  const char str2[] = "1242345384594503486734";
  int res1 = s21_memcmp(str1, str2, 256);
  int res2 = memcmp(str1, str2, 256);
  ck_assert_int_eq(sign_int(res1), sign_int(res2));
}
END_TEST

START_TEST(memcmp_11) {
  const char *str1 = NULL;
  const char str2[] = "1242345384594503486734";
  int res1 = s21_memcmp(str1, str2, 1);

  ck_assert_int_eq(sign_int(res1), -1);
}
END_TEST

START_TEST(memcmp_12) {
  const char str1[] = "1242345384594503486734";
  const char *str2 = NULL;
  int res1 = s21_memcmp(str1, str2, 1);

  ck_assert_int_eq(sign_int(res1), 1);
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *suite = suite_create("s21_memcmp_test");
  TCase *tcase_core = tcase_create("s21_memcmp_test");

  tcase_add_test(tcase_core, memcmp_1);
  tcase_add_test(tcase_core, memcmp_2);
  tcase_add_test(tcase_core, memcmp_3);
  tcase_add_test(tcase_core, memcmp_4);
  tcase_add_test(tcase_core, memcmp_5);
  tcase_add_test(tcase_core, memcmp_6);
  tcase_add_test(tcase_core, memcmp_7);
  tcase_add_test(tcase_core, memcmp_8);
  tcase_add_test(tcase_core, memcmp_9);
  tcase_add_test(tcase_core, memcmp_10);
  tcase_add_test(tcase_core, memcmp_11);
  tcase_add_test(tcase_core, memcmp_12);

  suite_add_tcase(suite, tcase_core);
  return suite;
}