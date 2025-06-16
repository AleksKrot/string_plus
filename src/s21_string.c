#include "s21_string.h"

#include <stdio.h>

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; str[len]; len++);
  return len + 1;
}

// Функция для поиска первого вхождения символа в памяти
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char ch = (unsigned char)c;
  const unsigned char *pt = (const unsigned char *)str;
  while (n--) {
    if (*pt == ch) return (void *)pt;
    pt++;
  }
  return S21_NULL;
}

// Функция для сравнения областей памяти
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;

  while (n--) {
    if (*s1 != *s2) return (int)*s1 - *s2;
    s1++;
    s2++;
  }
  return 0;
}

// Функция для копирования области памяти
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *srcx = (const unsigned char *)src;
  unsigned char *destx = (unsigned char *)dest;

  while (n--) {
    *destx++ = *srcx++;
  }
  return dest;
}

// Функция для заполнения памяти определенными символами
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *strx = (unsigned char *)str;
  const unsigned char ch = (unsigned char)c;
  while (n--) {
    *strx++ = ch;
  }
  return str;
}

// Функция для конкатенации двух строк
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  unsigned char *destx = (unsigned char *)dest;
  while (*destx != '\0') {
    destx++;
  }
  while (n-- && *src != '\0') {
    *destx++ = *src++;
  }
  *destx = '\0';
  return dest;
}

// Функция для определения местонахождения символа в строке
char *s21_strchr(const char *str, int c) {
  unsigned char *strx = (unsigned char *)str;
  const unsigned char ch = (unsigned char)c;
  while (1) {
    if (*strx == ch) return (char *)strx;
    if (*strx == '\0') break;
    strx++;
  }
  return S21_NULL;
}

// Функция для сравнения двух строк
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  unsigned char *strx1 = (unsigned char *)str1;
  unsigned char *strx2 = (unsigned char *)str2;
  while (n--) {
    if (*strx1 != *strx2) {
      return (int)*strx1 - (int)*strx2;
    }
    if (*strx1 == '\0')  // ???
      break;
    strx1++;
    strx2++;
  };
  return 0;
}

// Функция для копирование строки
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *destx = dest;
  while (n && *src != '\0') {
    *destx++ = *src++;
    n--;
  }
  while (n--) {
    *destx++ = '\0';
  }
  return dest;
}

// Функция для набора символов в строке
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  while (*str1 != '\0') {
    char *str2x = str2;
    while (*str2x != '\0') {
      if (*str1 == *str2x) return i;
      str2x++;
    }
    i++;
    str1++;
  }
  return i;
}

// Функция для поиска строки для любого набора символов
char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1 != '\0') {
    const char *str2x = str2;
    while (*str2x != '\0') {
      if (*str1 == *str2x) return str1;
      str2x++;
    }
    str1++;
  }
  return S21_NULL;
}

// Функция для определения местонахождения символа в строке
char *s21_strrchr(const char *str, int c) {
  const char ch = (char)c;
  s21_size_t len = s21_strlen(str);
  while (len--) {
    if (*(str + len) == ch) return *(str + len);
  }
  if (ch == '\0') return (char *)(str + s21_strlen(str));
  return S21_NULL;
}

// Функция для нахождения подстроки
char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') return haystack;
  while (*haystack != '\0') {
    char *haystackx = haystack;
    char *needlex = needle;
    while (*haystackx == *needlex && *needlex != '\0') {
      haystackx++;
      needlex++;
    }

    if (*needlex == '\0') return (char *)haystack;  // найдено совпадение

    haystack++;
  }
  return S21_NULL;
}

void *insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) return S21_NULL;
  char *result = S21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index < src_len) {
    *result = (char *)malloc(src_len + str_len + 1);
    if (result) {
      s21_size_t i = 0;

      for (; i < start_index; i++) {
        result[i] = src[i];
      }

      for (s21_size_t j = 0; j < str_len; j++) {
        result[i++] = str[j];
      }

      for (s21_size_t k = start_index; k < src_len; k++) {
        result[i++] = src[k];
      }
      result[i] = '\0';
    }
  }
  return (void *)result;
}

void *trim(const char *src, const char *trim_chars) {
  if (!src) return S21_NULL;
  char *result = S21_NULL;
  const char *set = trim_chars ? trim_chars : " \t\n\r\f\v";

  s21_size_t src_len = s21_strlen(src);

  s21_size_t lead_char = 0;
  s21_size_t trail_char = src_len;

  while (src[lead_char] && s21_strchr(set, src[lead_char])) {
    lead_char++;
  }
  while (lead_char < trail_char && s21_strchr(set, src[trail_char - 1])) {
    trail_char--;
  }
  s21_size_t new_len = trail_char - lead_char;
  *result = malloc(new_len + 1);

  if (result) {
    for (s21_size_t i = 0; i < new_len; i++) {
      result[i] = src[lead_char + i];
    }
    result[trail_char] = '\0';
  }
  return (void *)result;

char *s21_strtok(char *str, const char *delim) {
  static char *last;

  if (str != S21_NULL) {
    last = str;
  } else if (last == S21_NULL) {
    return S21_NULL;
  }

  // Пропуск начальных разделителей
  while (*last && s21_strchr(delim, *last)) {
    last++;
  }

  if (*last == '\0') return S21_NULL;

  char *token_start = last;

  // Идём до следующего разделителя или конца строки
  while (*last && s21_strchr(delim, *last) == S21_NULL) {
    last++;
  }

  if (*last) {
    *last = '\0';  // завершение текущего токена
    last++;        // указатель сдвигаем на следующий символ
  }

  return token_start;

}