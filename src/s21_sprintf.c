#include "s21_sprintf.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>  // Предназначена для работы с функциями с переменным числом аргументов
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *start = str;

  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    }

    format++;  // Skip '%'

    if (*format == '%') {
      *str++ = *format++;
      continue;
    }

    Format fmt;
    init_format(&fmt);
    format = parse_format(format, &fmt);
    process_format(&fmt, args, &str);
  }

  *str = '\0';
  va_end(args);
  return str - start;
}

const char *parse_format(const char *fmt, Format *format) {
  const char *p = fmt;
  const char *start = p;  // Сохраняем начальную позицию

  // Parse flags
  while (*p == '-' || *p == '+' || *p == ' ' || *p == '0') {
    if (*p == '-')
      format->flags.minus = true;
    else if (*p == '+')
      format->flags.plus = true;
    else if (*p == ' ')
      format->flags.space = true;
    else if (*p == '0')
      format->flags.zero = true;
    p++;
  }

  // Parse width
  if (isdigit(*p)) {
    format->width.number = 0;
    while (isdigit(*p)) {
      format->width.number = format->width.number * 10 + (*p - '0');
      p++;
    }
  }

  // Parse precision
  if (*p == '.') {
    p++;
    format->precision.explicit = true;
    format->precision.number = 0;
    while (isdigit(*p)) {
      format->precision.number = format->precision.number * 10 + (*p - '0');
      p++;
    }
    // Если просто точка без числа - точность 0
    if (p == start + 1) {
      format->precision.number = 0;
    }
  }

  // Parse length
  if (*p == 'h') {
    format->length.h = true;
    p++;
  } else if (*p == 'l') {
    format->length.l = true;
    p++;
  }

  // Parse specifier
  switch (*p) {
    case 'c':
      format->spec.c = true;
      break;
    case 'd':
      format->spec.d = true;
      break;
    case 'f':
      format->spec.f = true;
      break;
    case 's':
      format->spec.s = true;
      break;
    case 'u':
      format->spec.u = true;
      break;
    case '%':
      format->spec.percent = true;
      break;
    default:
      return fmt;  // Unknown specifier
  }

  return p + 1;
}

void process_format(Format *format, va_list args, char **buffer) {
  char temp[256];
  char *ptr = temp;
  char num_str[64];
  int len = 0;

  if (format->spec.c) {
    // Обработка %c
    char c = (char)va_arg(args, int);
    int width = format->width.number > 0 ? format->width.number : 1;

    if (format->flags.minus) {
      *ptr++ = c;
      for (int i = 1; i < width; i++) {
        *ptr++ = ' ';
      }
    } else {
      // Выравнивание вправо: пробелы + символ
      for (int i = 1; i < width; i++) {
        *ptr++ = ' ';
      }
      *ptr++ = c;
    }
  } else if (format->spec.d) {
    // Обработка %d
    long num = format->length.l ? va_arg(args, long) : va_arg(args, int);
    if (format->length.h) num = (short)num;

    int_to_str(labs(num), num_str);
    len = s21_strlen(num_str);

    // Обработка знака
    if (num < 0) {
      s21_memmove(num_str + 1, num_str, len + 1);
      num_str[0] = '-';
      len++;
    } else if (format->flags.plus) {
      s21_memmove(num_str + 1, num_str, len + 1);
      num_str[0] = '+';
      len++;
    } else if (format->flags.space) {
      s21_memmove(num_str + 1, num_str, len + 1);
      num_str[0] = ' ';
      len++;
    }

    // Обработка точности
    if (format->precision.explicit) {
      int precision = format->precision.number;
      if (precision > len) {
        int padding = precision - (num_str[0] == '-' || num_str[0] == '+' ||
                                           num_str[0] == ' '
                                       ? len - 1
                                       : len);
        if (padding > 0) {
          char *start = num_str;
          if (num_str[0] == '-' || num_str[0] == '+' || num_str[0] == ' ') {
            start++;
          }
          s21_memmove(start + padding, start, len + 1);
          s21_memset(start, '0', padding);
          len += padding;
        }
      }
    }

    // Обработка ширины
    if (format->width.number > len) {
      int padding = format->width.number - len;
      if (format->flags.minus) {
        // Выравнивание влево
        s21_strcpy(ptr, num_str);
        ptr += len;
        s21_memset(ptr, ' ', padding);
        ptr += padding;
      } else if (format->flags.zero && !format->precision.explicit) {
        // Нулевое заполнение
        if (num_str[0] == '-' || num_str[0] == '+' || num_str[0] == ' ') {
          *ptr++ = num_str[0];
          s21_memset(ptr, '0', padding);
          ptr += padding;
          s21_strcpy(ptr, num_str + 1);
          ptr += len - 1;
        } else {
          s21_memset(ptr, '0', padding);
          ptr += padding;
          s21_strcpy(ptr, num_str);
          ptr += len;
        }
      } else {
        // Выравнивание вправо
        s21_memset(ptr, ' ', padding);
        ptr += padding;
        s21_strcpy(ptr, num_str);
        ptr += len;
      }
    } else {
      s21_strcpy(ptr, num_str);
      ptr += len;
    }
  } else if (format->spec.f) {
    // Обработка %f
    double num = va_arg(args, double);
    int precision = format->precision.explicit ? format->precision.number : 6;

    double_to_str(num, precision, num_str);
    len = s21_strlen(num_str);

    // Обработка ширины
    if (format->width.number > len) {
      int padding = format->width.number - len;
      if (format->flags.minus) {
        // Выравнивание влево
        s21_strcpy(ptr, num_str);
        ptr += len;
        s21_memset(ptr, ' ', padding);
        ptr += padding;
      } else if (format->flags.zero && !format->precision.explicit) {
        // Нулевое заполнение
        if (num_str[0] == '-' || num_str[0] == '+' || num_str[0] == ' ') {
          *ptr++ = num_str[0];
          s21_memset(ptr, '0', padding);
          ptr += padding;
          s21_strcpy(ptr, num_str + 1);
          ptr += len - 1;
        } else {
          s21_memset(ptr, '0', padding);
          ptr += padding;
          s21_strcpy(ptr, num_str);
          ptr += len;
        }
      } else {
        // Выравнивание вправо
        s21_memset(ptr, ' ', padding);
        ptr += padding;
        s21_strcpy(ptr, num_str);
        ptr += len;
      }
    } else {
      s21_strcpy(ptr, num_str);
      ptr += len;
    }
  } else if (format->spec.s) {
    // Обработка %s
    char *s = va_arg(args, char *);
    if (s == NULL) {
      s = "(null)";
    }

    int str_len = s21_strlen(s);
    int precision_len =
        format->precision.explicit
            ? (format->precision.number < str_len ? format->precision.number
                                                  : str_len)
            : str_len;

    // Обработка ширины
    if (format->width.number > precision_len) {
      int padding = format->width.number - precision_len;
      if (format->flags.minus) {
        // Выравнивание влево
        s21_strncpy(ptr, s, precision_len);
        ptr += precision_len;
        s21_memset(ptr, ' ', padding);
        ptr += padding;
      } else {
        // Выравнивание вправо
        s21_memset(ptr, format->flags.zero ? '0' : ' ', padding);
        ptr += padding;
        s21_strncpy(ptr, s, precision_len);
        ptr += precision_len;
      }
    } else {
      s21_strncpy(ptr, s, precision_len);
      ptr += precision_len;
    }
  } else if (format->spec.u) {
    // Обработка %u
    unsigned long num = format->length.l ? va_arg(args, unsigned long)
                                         : va_arg(args, unsigned int);
    if (format->length.h) num = (unsigned short)num;

    uint_to_str(num, num_str);
    len = s21_strlen(num_str);

    // Обработка точности
    if (format->precision.explicit) {
      int precision = format->precision.number;
      if (precision > len) {
        int padding = precision - len;
        s21_memmove(num_str + padding, num_str, len + 1);
        s21_memset(num_str, '0', padding);
        len = precision;
      }
    }

    // Обработка ширины
    if (format->width.number > len) {
      int padding = format->width.number - len;
      if (format->flags.minus) {
        // Выравнивание влево
        s21_strcpy(ptr, num_str);
        ptr += len;
        s21_memset(ptr, ' ', padding);
        ptr += padding;
      } else if (format->flags.zero && !format->precision.explicit) {
        // Нулевое заполнение
        s21_memmove(num_str + padding, num_str, len + 1);
        s21_memset(num_str, '0', padding);
        s21_strcpy(ptr, num_str);
        ptr += format->width.number;
      } else {
        // Выравнивание вправо
        s21_memset(ptr, ' ', padding);
        ptr += padding;
        s21_strcpy(ptr, num_str);
        ptr += len;
      }
    } else {
      s21_strcpy(ptr, num_str);
      ptr += len;
    }
  } else if (format->spec.percent) {
    // Обработка %%
    int width = format->width.number > 0 ? format->width.number : 1;

    if (format->flags.minus) {
      // Выравнивание влево: % + пробелы
      *ptr++ = '%';
      for (int i = 1; i < width; i++) {
        *ptr++ = ' ';
      }
    } else {
      // Выравнивание вправо: пробелы + %
      for (int i = 1; i < width; i++) {
        *ptr++ = ' ';
      }
      *ptr++ = '%';
    }
  }

  // Копирование в выходной буфер
  int total = ptr - temp;
  s21_memcpy(*buffer, temp, total);
  *buffer += total;
}

// Вспомогательная функция для преобразования числа в строку
void int_to_str(long num, char *str) {
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  int i = 0;
  int is_negative = 0;

  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  while (num != 0) {
    int digit = num % 10;
    str[i++] = digit + '0';
    num /= 10;
  }

  if (is_negative) {
    str[i++] = '-';
  }

  str[i] = '\0';

  // Разворачиваем строку
  int len = i;
  for (int j = 0; j < len / 2; j++) {
    char temp = str[j];
    str[j] = str[len - j - 1];
    str[len - j - 1] = temp;
  }
}

// Вспомогательная функция для преобразования unsigned числа в строку
void uint_to_str(unsigned long num, char *str) {
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  int i = 0;
  while (num != 0) {
    int digit = num % 10;
    str[i++] = digit + '0';
    num /= 10;
  }

  str[i] = '\0';

  // Разворачиваем строку
  int len = i;
  for (int j = 0; j < len / 2; j++) {
    char temp = str[j];
    str[j] = str[len - j - 1];
    str[len - j - 1] = temp;
  }
}

// Вспомогательная функция для преобразования double в строку
void double_to_str(double num, int precision, char *str) {
  // Если точность не указана, используем 6 знаков по умолчанию
  if (precision < 0) precision = 6;

  // Обработка отрицательных чисел
  int is_negative = num < 0;
  if (is_negative) {
    num = -num;
  }

  // Округление
  double rounder = 0.5;
  for (int i = 0; i < precision; i++) {
    rounder /= 10.0;
  }
  num += rounder;

  // Обработка целой части
  long int_part = (long)num;
  int_to_str(int_part, str);
  s21_size_t len = s21_strlen(str);

  // Добавляем знак минуса для отрицательных чисел
  if (is_negative) {
    s21_memmove(str + 1, str, len + 1);
    str[0] = '-';
    len++;
  }

  // Обработка дробной части
  if (precision > 0) {
    double frac_part = num - int_part;
    char *ptr = str + len;
    *ptr++ = '.';

    // Извлечение цифр
    for (int i = 0; i < precision; i++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      *ptr++ = digit + '0';
      frac_part -= digit;
    }
    *ptr = '\0';
  } else if (precision == 0) {
    // Без дробной части
    str[len] = '\0';
  }
}