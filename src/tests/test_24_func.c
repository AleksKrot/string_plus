#include "test.h"

/////////////////////////////// Nan Nan

START_TEST(testing_memchr) {
  const char str[] = "http://www.tutorialspoint.com";
  const char ch = '.';
  s21_SIZE_T n = 10;
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(testing_memcmp) {
  const char str1[] = "00001234ttep://www.tutorialspoint.com";
  const char str2[] = "000dd012ffe34http933883";
  int n = 4;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(testing_memcpy) {
  const char str[] = "1234567";
  unsigned char dest[10] = " ";
  s21_SIZE_T n = 4;
  ck_assert_pstr_eq(s21_memcpy(dest, str, n), memcpy(dest, str, n));
}
END_TEST

START_TEST(testing_memmove) {
  const char str[] = "fffffff";
  unsigned char dest[10] = "eeeeeee";
  s21_SIZE_T n = 5;
  ck_assert_pstr_eq(s21_memmove(dest, str, n), memmove(dest, str, n));
}
END_TEST

START_TEST(testing_memset) {
  unsigned char str[15] = "123456789";
  const char ch = '/';
  s21_SIZE_T n = 3;
  ck_assert_pstr_eq(s21_memset(str, ch, n), memset(str, ch, n));
}
END_TEST

////////////////////////////// wellpetr

START_TEST(strcat_test) {
  char stroka1[100] = "fisdofsferigjfdl";
  char stroka2[] = "csaffsd";
  ck_assert_pstr_eq(s21_strcat(stroka1, stroka2), strcat(stroka1, stroka2));
}
END_TEST

START_TEST(strncat_test) {
  char stroka1[100] = "qwertyuiop";
  char stroka2[] = "asdfghjkl";
  s21_SIZE_T n = 3;
  ck_assert_pstr_eq(s21_strncat(stroka1, stroka2, n),
                    strncat(stroka1, stroka2, n));
}
END_TEST

START_TEST(strchr_test) {
  char stroka1[] = "abrakadabra";
  ck_assert_pstr_eq(s21_strchr(stroka1, 'r'), strchr(stroka1, 'r'));
  ck_assert_pstr_eq(s21_strchr(stroka1, 'w'), strchr(stroka1, 'w'));
}
END_TEST

START_TEST(strcmp_test) {
  char stroka1[] = "let's compare these strings";
  char stroka2[] = "let's not compare these strings";
  ck_assert_int_eq(s21_strcmp(stroka1, stroka2), strcmp(stroka1, stroka2));
  char stroka3[] = "same string";
  char stroka4[] = "same string";
  ck_assert_int_eq(s21_strcmp(stroka3, stroka4), strcmp(stroka3, stroka4));
}
END_TEST

START_TEST(strncmp_test) {
  char stroka1[] = "comparison";
  char stroka2[] = "comparidaughter";
  ck_assert_int_eq(s21_strncmp(stroka1, stroka2, 7),
                   strncmp(stroka1, stroka2, 7));
  ck_assert_int_eq(s21_strncmp(stroka1, stroka2, 8),
                   strncmp(stroka1, stroka2, 8));
  ck_assert_int_eq(s21_strncmp("comp", "comp", 8), strncmp("comp", "comp", 8));
}
END_TEST

//////////////////////////////// Roonneele

START_TEST(testing_strcpy) {
  char massTest[] = "abrakodabra";
  char massTest2[100] = {'\0'};
  ck_assert_pstr_eq(s21_strcpy(massTest, massTest2),
                    strcpy(massTest, massTest2));
}
END_TEST

START_TEST(testing_strncpy) {
  char massTest[] = "abrakodabra";
  char massTest2[100] = {'\0'};
  ck_assert_pstr_eq(s21_strncpy(massTest, massTest2, 4),
                    strncpy(massTest, massTest2, 4));
}
END_TEST

START_TEST(testing_strcspn) {
  char massTest[] = "abrakodabra";
  char massTest2[] = "kr";
  ck_assert_int_eq(s21_strcspn(massTest, massTest2),
                   strcspn(massTest, massTest2));
}
END_TEST

START_TEST(testing_strerror) {
  ck_assert_pstr_eq(s21_strerror(4), strerror(4));
  ck_assert_pstr_eq(s21_strerror(404), strerror(404));
  ck_assert_pstr_eq(s21_strerror(400), strerror(400));
  ck_assert_pstr_eq(s21_strerror(007), strerror(007));
  ck_assert_pstr_eq(s21_strerror(-1000), strerror(-1000));
  ck_assert_pstr_eq(s21_strerror(-1), strerror(-1));
}
END_TEST

START_TEST(testing_strlen) {
  char massTest[] = "abrakodabra";
  ck_assert_int_eq(s21_strlen(massTest), strlen(massTest));
}
END_TEST

START_TEST(testing_strpbrk) {
  char massTest[] = "abrakodabra";
  char massTest2[] = "kr";
  ck_assert_pstr_eq(s21_strpbrk(massTest, massTest2),
                    strpbrk(massTest, massTest2));
}
END_TEST

START_TEST(testing_strrchr) {
  char massTest[] = "abrakodabra";
  ck_assert_pstr_eq(s21_strrchr(massTest, 'd'), strrchr(massTest, 'd'));
}
END_TEST

START_TEST(testing_strspn) {
  char massTest[] = "abrakodabra";
  char massTest2[] = "roakb";
  ck_assert_int_eq(s21_strspn(massTest, massTest2),
                   strspn(massTest, massTest2));
}
END_TEST

START_TEST(testing_strstr) {
  char massTest[] = "abrakodabra";
  char massTest2[] = "doak";
  ck_assert_pstr_eq(s21_strstr(massTest, massTest2),
                    strstr(massTest, massTest2));
}
END_TEST

START_TEST(testing_strtok) {
  char massTest11[] = "abra koda ara/";
  char massTest12[] = "abra koda ara/";
  char massTest3[10] = " /";

  char *massTest21 = strtok(massTest11, massTest3);
  char *massTest22 = s21_strtok(massTest12, massTest3);
  while (massTest21 != s21_NULL) {
    ck_assert_pstr_eq(massTest21, massTest22);
    massTest21 = strtok(s21_NULL, massTest3);
    massTest22 = s21_strtok(s21_NULL, massTest3);
  }
  ck_assert_pstr_eq(s21_strtok(massTest21, massTest3),
                    strtok(massTest22, massTest3));
}
END_TEST

////////////////////////////////// kylebrea

START_TEST(testing_to_upper) {
  // big + small
  char *in1 = "AURINKOinen";
  char *res = s21_to_upper(in1);
  char *out1 = "AURINKOINEN";
  ck_assert_pstr_eq(res, out1);
  free(res);

  // big
  char *in2 = "AURINKOINEN";
  res = s21_to_upper(in2);
  char *out2 = "AURINKOINEN";
  ck_assert_pstr_eq(res, out2);
  free(res);

  // symbols
  char *in3 = "~^Aurinko~inen!*&^@*&368761726316876137491837";
  res = s21_to_upper(in3);
  char *out3 = "~^AURINKO~INEN!*&^@*&368761726316876137491837";
  ck_assert_pstr_eq(res, out3);
  free(res);

  // escape sequences
  char *in4 = "~Aurinko\nin\fe\vn!";
  res = s21_to_upper(in4);
  char *out4 = "~AURINKO\nIN\fE\vN!";
  ck_assert_pstr_eq(res, out4);
  free(res);
}
END_TEST

START_TEST(testing_to_lower) {
  // big + small
  char *in1 = "AURINKOinen";
  char *res = s21_to_lower(in1);
  char *out1 = "aurinkoinen";
  ck_assert_pstr_eq(res, out1);
  free(res);

  // big
  char *in2 = "AURINKOINEN";
  res = s21_to_lower(in2);
  char *out2 = "aurinkoinen";
  ck_assert_pstr_eq(res, out2);
  free(res);

  // symbols
  char *in3 = "~^Aurinko~inen!*&^@*&368761726316876137491837";
  res = s21_to_lower(in3);
  char *out3 = "~^aurinko~inen!*&^@*&368761726316876137491837";
  ck_assert_pstr_eq(res, out3);
  free(res);

  // escape sequences
  char *in4 = "~Aurinko\nin\fe\vn!";
  res = s21_to_lower(in4);
  char *out4 = "~aurinko\nin\fe\vn!";
  ck_assert_pstr_eq(res, out4);
  free(res);
}
END_TEST

START_TEST(testing_trim) {
  // two tc
  char *in1 = "  ^ ^ auRInkO inen! ^ ^ ^^ ";
  const char tc1[] = " ^";
  char *res1 = s21_trim(in1, tc1);
  char *out1 = "auRInkO inen!";
  ck_assert_pstr_eq(res1, out1);
  free(res1);

  // one tc
  char *in2 = "  ^ ^ auRInkO inen! ^ ^ ^^ ";
  const char tc2[] = " ";
  char *res2 = s21_trim(in2, tc2);
  char *out2 = "^ ^ auRInkO inen! ^ ^ ^^";
  ck_assert_pstr_eq(res2, out2);
  free(res2);

  // NULL tc + special characters
  char *in3 = "  \t\n^ ^ auRInkO inen! ^ ^ ^^\f\v ";
  const char *tc3 = s21_NULL;
  char *res3 = s21_trim(in3, tc3);
  char *out3 = "^ ^ auRInkO inen! ^ ^ ^^";
  ck_assert_pstr_eq(res3, out3);
  free(res3);

  // empty tc + special characters
  char *in4 = "  \t\n^ ^ auRInkO inen! ^ ^ ^^\f\v ";
  const char tc4[] = "";
  char *res4 = s21_trim(in4, tc4);
  char *out4 = "^ ^ auRInkO inen! ^ ^ ^^";
  ck_assert_pstr_eq(res4, out4);
  free(res4);

  // equal string and tc
  char *in5 = "Honda Chery Kia Mazda";
  const char tc5[] = "Honda Chery Kia Mazda";
  char *res5 = s21_trim(in5, tc5);
  char *out5 = "";
  ck_assert_pstr_eq(res5, out5);
  free(res5);

  // same string and tc ending
  char *in6 = "Honda Chery Kia Mazda";
  const char tc6[] = "Honda";
  char *res6 = s21_trim(in6, tc6);
  char *out6 = " Chery Kia Maz";
  ck_assert_pstr_eq(res6, out6);
  free(res6);
}
END_TEST

START_TEST(testing_insert) {
  char *str = "insert";
  char *str2 = "insertert";
  const char ins[] = "ert";
  const size_t n = 3;
  char *res = s21_insert(str, ins, n);
  ck_assert_pstr_eq(res, str2);
  ck_assert_pstr_eq(s21_insert(s21_NULL, ins, n), s21_NULL);
  free(res);
}
END_TEST

Suite *test_24_func(void) {
  Suite *s = suite_create("\033[45m-=S21_24_func=-\033[0m");
  TCase *tc = tcase_create("sprintf_tc");

  tcase_add_test(tc, testing_memchr);
  tcase_add_test(tc, testing_memcmp);
  tcase_add_test(tc, testing_memcpy);
  tcase_add_test(tc, testing_memmove);
  tcase_add_test(tc, testing_memset);
  tcase_add_test(tc, strcat_test);
  tcase_add_test(tc, strncat_test);
  tcase_add_test(tc, strchr_test);
  tcase_add_test(tc, strcmp_test);
  tcase_add_test(tc, strncmp_test);
  tcase_add_test(tc, testing_strcpy);
  tcase_add_test(tc, testing_strncpy);
  tcase_add_test(tc, testing_strcspn);
  tcase_add_test(tc, testing_strerror);
  tcase_add_test(tc, testing_strlen);
  tcase_add_test(tc, testing_strpbrk);
  tcase_add_test(tc, testing_strrchr);
  tcase_add_test(tc, testing_strspn);
  tcase_add_test(tc, testing_strstr);
  tcase_add_test(tc, testing_strtok);
  tcase_add_test(tc, testing_to_upper);
  tcase_add_test(tc, testing_to_lower);
  tcase_add_test(tc, testing_trim);
  tcase_add_test(tc, testing_insert);

  suite_add_tcase(s, tc);

  return s;
}
