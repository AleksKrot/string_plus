#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_sprintf.h"

#define TEST_BUFFER_SIZE 256
#define RUN_TEST(test_func)              \
  printf("Running %s...\n", #test_func); \
  test_func();                           \
  printf("%s passed!\n\n", #test_func)

void print_test_result(const char* format, const char* expected,
                       const char* actual, int success) {
  printf("Test: %s\n", format);
  printf("Expected: \"%s\"\n", expected);
  printf("Actual:   \"%s\"\n", actual);
  printf("Result:   %s\n\n", success ? "PASSED" : "FAILED");
}

void test_d_specifier() {
  char buffer[TEST_BUFFER_SIZE];
  const char* expected;
  int success;

  // Базовые тесты
  expected = "123";
  s21_sprintf(buffer, "%d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%d", expected, buffer, success);
  assert(success);

  expected = "-456";
  s21_sprintf(buffer, "%d", -456);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%d (negative)", expected, buffer, success);
  assert(success);

  // Тесты с шириной
  expected = "  123";
  s21_sprintf(buffer, "%5d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%5d", expected, buffer, success);
  assert(success);

  expected = "123  ";
  s21_sprintf(buffer, "%-5d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%-5d", expected, buffer, success);
  assert(success);

  // Тесты с флагом 0
  expected = "00123";
  s21_sprintf(buffer, "%05d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%05d", expected, buffer, success);
  assert(success);

  // Тесты с точностью
  expected = "0123";
  s21_sprintf(buffer, "%.4d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%.4d", expected, buffer, success);
  assert(success);

  // Комбинированные тесты
  expected = "   00123";
  s21_sprintf(buffer, "%8.5d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%8.5d", expected, buffer, success);
  assert(success);
}

void test_f_specifier() {
  char buffer[TEST_BUFFER_SIZE];
  const char* expected;
  int success;

  // Базовые тесты
  expected = "3.140000";
  s21_sprintf(buffer, "%f", 3.14);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%f", expected, buffer, success);
  assert(success);

  expected = "3.14";
  s21_sprintf(buffer, "%.2f", 3.1415);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%.2f", expected, buffer, success);
  assert(success);

  // Тесты с шириной
  expected = "  3.140000";
  s21_sprintf(buffer, "%10f", 3.14);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%10f", expected, buffer, success);
  assert(success);

  // Тесты с флагом 0
  expected = "003.140000";
  s21_sprintf(buffer, "%010f", 3.14);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%010f", expected, buffer, success);
  assert(success);

  // Комбинированные тесты
  expected = "    3.14";
  s21_sprintf(buffer, "%8.2f", 3.1415);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%8.2f", expected, buffer, success);
  assert(success);

  expected = "3.14    ";
  s21_sprintf(buffer, "%-8.2f", 3.1415);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%-8.2f", expected, buffer, success);
  assert(success);
}

void test_s_specifier() {
  char buffer[TEST_BUFFER_SIZE];
  const char* expected;
  int success;

  // Базовые тесты
  expected = "hello";
  s21_sprintf(buffer, "%s", "hello");
  success = strcmp(buffer, expected) == 0;
  print_test_result("%s", expected, buffer, success);
  assert(success);

  // Тест с NULL
  expected = "(null)";
  s21_sprintf(buffer, "%s", NULL);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%s (NULL)", expected, buffer, success);
  assert(success);

  // Тесты с шириной
  expected = "  hello";
  s21_sprintf(buffer, "%7s", "hello");
  success = strcmp(buffer, expected) == 0;
  print_test_result("%7s", expected, buffer, success);
  assert(success);

  // Тесты с точностью
  expected = "hel";
  s21_sprintf(buffer, "%.3s", "hello");
  success = strcmp(buffer, expected) == 0;
  print_test_result("%.3s", expected, buffer, success);
  assert(success);

  // Комбинированные тесты
  expected = "  hel";
  s21_sprintf(buffer, "%5.3s", "hello");
  success = strcmp(buffer, expected) == 0;
  print_test_result("%5.3s", expected, buffer, success);
  assert(success);
}

void test_c_specifier() {
  char buffer[TEST_BUFFER_SIZE];
  const char* expected;
  int success;

  // Базовые тесты
  expected = "A";
  s21_sprintf(buffer, "%c", 'A');
  success = strcmp(buffer, expected) == 0;
  print_test_result("%c", expected, buffer, success);
  assert(success);

  // Тесты с шириной
  expected = "  A";
  s21_sprintf(buffer, "%3c", 'A');
  success = strcmp(buffer, expected) == 0;
  print_test_result("%3c", expected, buffer, success);
  assert(success);

  expected = "A  ";
  s21_sprintf(buffer, "%-3c", 'A');
  success = strcmp(buffer, expected) == 0;
  print_test_result("%-3c", expected, buffer, success);
  assert(success);
}

void test_u_specifier() {
  char buffer[TEST_BUFFER_SIZE];
  const char* expected;
  int success;

  // Базовые тесты
  expected = "123";
  s21_sprintf(buffer, "%u", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%u", expected, buffer, success);
  assert(success);

  // Тесты с шириной
  expected = "00123";
  s21_sprintf(buffer, "%05u", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%05u", expected, buffer, success);
  assert(success);
}

void test_percent_specifier() {
  char buffer[TEST_BUFFER_SIZE];
  const char* expected;
  int success;

  expected = "%";
  s21_sprintf(buffer, "%%");
  success = strcmp(buffer, expected) == 0;
  print_test_result("%%", expected, buffer, success);
  assert(success);

  expected = "  %";
  s21_sprintf(buffer, "%3%");
  success = strcmp(buffer, expected) == 0;
  print_test_result("%3%", expected, buffer, success);
  assert(success);
}

void test_flags_combinations() {
  char buffer[TEST_BUFFER_SIZE];
  const char* expected;
  int success;

  // Тест флага +
  expected = "+123";
  s21_sprintf(buffer, "%+d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%+d", expected, buffer, success);
  assert(success);

  // Тест флага пробела
  expected = " 123";
  s21_sprintf(buffer, "% d", 123);
  success = strcmp(buffer, expected) == 0;
  print_test_result("% d", expected, buffer, success);
  assert(success);

  // Комбинированный тест
  expected = "+003.14";
  s21_sprintf(buffer, "%+07.2f", 3.1415);
  success = strcmp(buffer, expected) == 0;
  print_test_result("%+07.2f", expected, buffer, success);
  assert(success);
}

int main() {
  RUN_TEST(test_d_specifier);
  RUN_TEST(test_f_specifier);
  RUN_TEST(test_s_specifier);
  RUN_TEST(test_c_specifier);
  RUN_TEST(test_u_specifier);
  RUN_TEST(test_percent_specifier);
  RUN_TEST(test_flags_combinations);

  printf("All tests passed successfully!\n");
  return 0;
}