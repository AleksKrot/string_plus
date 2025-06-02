#include "s21_string_function.h"

#include <stdio.h>

void *s21_memchr(const void *str, int c, size_t n) {
  if (str) {  // В стандартной memchr проверки нет
    const unsigned char *p = str;
    for (size_t i = 0; i < n; i++) {
      if (p[i] == (unsigned char)c) {
        return (void *)(p + i);
      }
    }
  }
  return S21_NULL; // В стандартной memchr также два выхода из функции
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  // По стандарту: функция не должна обрабатывать NULL специально. 
  const unsigned char *p1 = str1, *p2 = str2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] - p2[i];
    }
  }
  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {

}






size_t s21_strlen(const char *str) {
  size_t len = 0;
  if (str) {  // В стандартной реализации нет проверки на NULL
    for (; *(str + len); len++);  // Здесь происходит разыменование указателя,
                                  // т.е. получение символа в позиции len
  }
  return len;
}

void *s21_to_upper(const char *str) {
  char *result = S21_NULL;
  if (str) {
    // Вычисляем длину строки
    s21_size_t len = s21_strlen(str);
    // Выделяем память под новую строку (+1 для нуль-терминатора)
    result = malloc(len + 1);

    if (result) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          result[i] = str[i] - ('a' - 'A');  // Переводим в верхний регистр
        } else {
          result[i] = str[i];  // Копируем без изменений
        }
      }
      result[len] = '\0';  // Добавление терминатора
    }
  }

  return result;
}

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str) {
    // Вычисляем длину строки
    s21_size_t len = s21_strlen(str);
    // Выделяем память под новую строку (+1 для нуль-терминатора)
    result = malloc(len + 1);

    if (result) {
      for (s21_size_t i = 0; i < len; i++) {  // todo Дублирование кода???
        if (str[i] >= 'A' && str[i] <= 'Z') {
          result[i] = str[i] + ('a' - 'A');  // Переводим в нижний регистр
        } else {
          result[i] = str[i];  // Копируем без изменений
        }
      }
      result[len] = '\0';  // Явное добавление терминатора
    }
  }

  return result;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *result = S21_NULL;
  if (src && str && start_index <= s21_strlen(src)) {
    // Вычисляем длины строк
    size_t src_len = s21_strlen(src);
    size_t str_len = s21_strlen(str);
    result = malloc(src_len + str_len + 1);  // Выделяем память для новой строки

    if (result) {
      // Копируем часть до start_index
      size_t i;
      for (i = 0; i < start_index; i++) {
        result[i] = src[i];
      }

      // Вставляем строку str
      for (size_t j = 0; j < str_len; j++) {
        result[i + j] = str[j];
      }

      // Копируем оставшуюся часть src
      for (size_t k = 0; k < src_len - start_index; k++) {
        result[i + str_len + k] = src[start_index + k];
      }
      result[src_len + str_len] = '\0';
    }
  }
  return result;
}