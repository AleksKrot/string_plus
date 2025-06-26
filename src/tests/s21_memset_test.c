#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

typedef size_t s21_size_t;

// Объявление тестируемой функции
void *s21_memset(void *str, int c, s21_size_t n);
static int compare_memory(const void *s1, const void *s2, s21_size_t n);
Suite *memset_suite(void);

int main(void) {
  int number_failed;
  Suite *s;  // Контейнер, который хранит группу связанных тестов
  SRunner *sr;  // Структура для запуска тестов

  s = memset_suite();  // функция, создающая набор тестов
  sr = srunner_create(s);  // Передаем Suite, который нужно запустить

  srunner_run_all(sr, CK_NORMAL);  // Запуск всех тестов
  number_failed =
      srunner_ntests_failed(sr);  // Возвращает количество тестов, которые
                                  // завершились с ошибкой (FAILED)
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// Тестовые случаи
START_TEST(test_memset_basic) {  // Проверяет базовый случай заполнения части
                                 // строки символом
  char str1[32] = "hello, world";
  char str2[32] = "hello, world";

  int c = '*';
  size_t n = 5;

  void *res1 = s21_memset(str1, c, n);
  void *res2 = memset(str2, c, n);

  // Отладочная печать ДО проверок
  // printf("\nDebug after memset:\n");
  // printf("s21: [%.*s][%s]\n", (int)n, str1, str1 + n);
  // printf("std: [%.*s][%s]\n", (int)n, str2, str2 + n);
  // printf("Full buffers:\ns21: %s\nstd: %s\n", str1, str2);

  // Проверки
  ck_assert_ptr_eq(res1, str1);
  ck_assert_ptr_eq(res2, str2);

  const char *expected_remainder = ", world";
  ck_assert_str_eq(str1 + n, expected_remainder);
  ck_assert_str_eq(str2 + n, expected_remainder);

  ck_assert_mem_eq(str1, str2, 32);
}
END_TEST

START_TEST(test_memset_full_length) {  // Проверяет заполнение всей строки
  char str1[20] = "hello, world";
  char str2[20] = "hello, world";
  int c = '$';
  size_t n = strlen(str1);

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_int_eq(compare_memory(str1, str2, 20), 0);
}
END_TEST

START_TEST(
    test_memset_zero_length) {  // Проверяет граничный случай с нулевой длиной
  char str1[20] = "hello, world";
  char str2[20] = "hello, world";
  int c = '#';
  s21_size_t n = 0;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_int_eq(compare_memory(str1, str2, 20), 0);
}
END_TEST

START_TEST(
    test_memset_null_terminator) {  // Проверяет заполнение нулевыми символами
  char str1[20] = "hello, world";
  char str2[20] = "hello, world";
  int c = '\0';
  s21_size_t n = 5;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_int_eq(compare_memory(str1, str2, 20), 0);
}
END_TEST

START_TEST(test_memset_non_ascii) {  // Проверяет работу с не-ASCII символами
  char str1[20] = "hello, world";
  char str2[20] = "hello, world";
  int c = 0x80;  // Не-ASCII символ
  s21_size_t n = 7;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_int_eq(compare_memory(str1, str2, 20), 0); // Макрос для проверки равенства двух целых чисел в модульных тестах
}
END_TEST

START_TEST(test_memset_large_buffer) {  // Проверяет работу с большим буфером
  const s21_size_t size = 1024;
  char *str1 = malloc(size);
  char *str2 = malloc(size);
  int c = '@';

  s21_memset(str1, c, size);
  memset(str2, c, size);

  ck_assert_int_eq(compare_memory(str1, str2, size), 0);

  free(str1);
  free(str2);
}
END_TEST

START_TEST(test_memset_partial_overwrite) {  // Проверяет частичное заполнение с
                                             // середины строки
  char str1[20] = "hello, world";
  char str2[20] = "hello, world";
  int c = 'x';
  s21_size_t n = 3;

  s21_memset(str1 + 4, c, n);
  memset(str2 + 4, c, n);

  ck_assert_int_eq(compare_memory(str1, str2, 20), 0);
}
END_TEST

START_TEST(test_memset_int_array) {  // Проверяет работу с массивом int (не
                                     // символьным типом)
  int arr1[5] = {1, 2, 3, 4, 5};
  int arr2[5] = {1, 2, 3, 4, 5};
  int c = 0xFF;
  s21_size_t n = 5 * sizeof(int);

  s21_memset(arr1, c, n);
  memset(arr2, c, n);

  ck_assert_int_eq(compare_memory(arr1, arr2, n), 0);
}
END_TEST

Suite *memset_suite(void) {
  Suite *s;
  TCase *tc_core;  // Подгруппа тестов внутри Suite

  s = suite_create("s21_memset");  // Создаем набор с именем "s21_memset"

  tc_core = tcase_create("Core");  // Создаем Test Case (подгруппу тестов)

  // Добавляем тесты в TCase
  tcase_add_test(tc_core, test_memset_basic);
  tcase_add_test(tc_core, test_memset_full_length);
  tcase_add_test(tc_core, test_memset_zero_length);
  tcase_add_test(tc_core, test_memset_null_terminator);
  tcase_add_test(tc_core, test_memset_non_ascii);
  tcase_add_test(tc_core, test_memset_large_buffer);
  tcase_add_test(tc_core, test_memset_partial_overwrite);
  tcase_add_test(tc_core, test_memset_int_array);

  // Добавляем TCase в Suite
  suite_add_tcase(s, tc_core);

  return s;  // Возвращаем готовый Suite
}

// Вспомогательная функция для сравнения массивов
static int compare_memory(const void *s1, const void *s2, s21_size_t n) {
  const unsigned char *p1 = s1, *p2 = s2;
  for (; n--; p1++, p2++) {
    if (*p1 != *p2) {
      return -1;
    }
  }
  return 0;
}
