#include "s21_string.h"

//  поиск первого вхождения символа c в первых n байтах строки, на которую
//  указывает аргумент str
void *s21_memchr(const void *str, int c, size_t n) {
  size_t success = n;
  const unsigned char *ptr_str = (const unsigned char *)str;
  if (str != NULL) {
    size_t i = 0;
    while (i < n && success == n) {
      if (ptr_str[i] == (unsigned char)c) {
        success = i;
      }
      i++;
    }
  }
  return success == n ? NULL : (void *)(ptr_str + success);
}

// cравнивает первые n байт строк str1 и str2
int s21_memcmp(const void *str1, const void *str2, size_t n) {
  int ret = 0;
  if (str1 != NULL && str2 != NULL) {
    const unsigned char *ptr_str1 = (const unsigned char *)str1;
    const unsigned char *ptr_str2 = (const unsigned char *)str2;
    for (size_t i = 0; i < n && ret == 0; i++) {
      if (ptr_str1[i] != ptr_str2[i]) {
        ret = (int)ptr_str1[i] - (int)ptr_str2[i];
      }
    }
  } else if (str1 != str2) {
    if (str1 == NULL) {
      ret = -1;
    } else {
      ret = 1;
    }
  }
  return ret;
}

// копирует n символов из src в dest
void *s21_memcpy(void *dest, const void *src, size_t n) {
  if (dest != NULL && src != NULL) {
    unsigned char *ptr_dest = (unsigned char *)dest;
    const unsigned char *ptr_src = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++) {
      ptr_dest[i] = ptr_src[i];
    }
  }
  return dest;
}

// копирует символ c в первые n символов строки, на которую указывает str
void *s21_memset(void *str, int c, size_t n) {
  if (str != NULL) {
    unsigned char *ptr_str = (unsigned char *)str;
    for (size_t i = 0; i < n; i++) {
      ptr_str[i] = (unsigned char)c;
    }
  }
  return str;
}

// добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов
char *s21_strncat(char *dest, const char *src, size_t n) {
  if (dest != NULL && src != NULL) {
    size_t size_dest = s21_strlen(dest);
    size_t count = 0;
    while (src[count] != '\0' || count < n) {
      dest[size_dest + count] = src[count];
      count++;
    }
    dest[size_dest + count] = '\0';
  }
  return dest;
}

// выполняет поиск первого вхождения символа c в строке, на которую указывает
// аргумент str
char *s21_strchr(const char *str, int c) {
  return (char *)s21_memchr((const void *)str, c, s21_strlen(str) + 1);
}

// сравнивает не более первых n байт строк str1 и str2
int s21_strncmp(const char *str1, const char *str2, size_t n) {
  return s21_memcmp((const void *)str1, (const void *)str2, n);
}

// копирует до n символов из строки, на которую указывает src, в dest
char *s21_strncpy(char *dest, const char *src, size_t n) {
  return (char *)s21_memcpy((void *)dest, (const void *)src, n);
}

// вычисляет длину строки
size_t s21_strlen(const char *src) {
  size_t ret = 0;
  if (src != NULL) {
    size_t i = ret;
    while (src[i] != '\0') {
      i++;
    }
    ret = i;
  }
  return ret;
}