#ifndef S21_STRING_H
#define S21_STRING_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define is_flag(c)                                                             \
  ((c) == '-' || (c) == '+' || (c) == ' ' || (c) == '#' || (c) == '0')

#define is_digit(c) ((c) >= '0' && (c) <= '9')

#define is_length(c) ((c) == 'h' || (c) == 'l' || (c) == 'L')

#define is_specifier(c)                                                        \
  ((c) == 'c' || (c) == 'd' || (c) == 'i' || (c) == 'e' || (c) == 'E' ||       \
   (c) == 'f' || (c) == 'g' || (c) == 'G' || (c) == 'o' || (c) == 's' ||       \
   (c) == 'u' || (c) == 'x' || (c) == 'X' || (c) == 'p' || (c) == 'n' ||       \
   (c) == '%')

#define is_space(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')

typedef struct Flags {
  // flags
  bool alignment; // выравнивание по левому краю
  bool sign;      // выводить знак +
  bool space; // Если знак не будет выведен, перед значением вставляется пробел
  bool sharp; // префиксы для oct/hex ...
  bool zero;  // ставить 0 перед числом
  bool is_negative;

  bool is_up; // заглавные буквы

  size_t width; // минимальное количество печатаемых символов (ширина)
  int accuracy; // точность для double, ширина для int

  char size; // длина h, l, L
  bool is_g;

} Flags;

// функция sprintf
int s21_sprintf(char *str, const char *format, ...);

// функции string.h
void *s21_memchr(const void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memset(void *str, int c, size_t n);
char *s21_strncat(char *dest, const char *src, size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strncpy(char *dest, const char *src, size_t n);

size_t s21_strlen(const char *src);

// преобразование к строке
void s21_int_to_str(char *result, long long int num, int num_sys, Flags *flags);
void s21_uint_to_str(char *result, unsigned long long int num, int num_sys,
                     Flags *flags);

void s21_float_to_str(char *result, long double num, Flags flags);
void s21_notat_float_to_str(char *result, long double num, Flags flags);
void s21_g_float_to_str(char *result, long double num, Flags *flags);

void s21_char_to_str(char **result, char c);
void s21_str_to_str(char *result, char *str, Flags *flags);
void s21_ptr_to_str(char *result, void *ptr, Flags *flags);

#endif