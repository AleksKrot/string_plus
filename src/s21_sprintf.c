#include "s21_sprintf.h"

#include <stdarg.h>  // Предназначена для работы с функциями с переменным числом аргументов
#include <stdio.h>

#include "s21_string.h"

int main() {
  Format format;

  char buffer[256];
  int count = sprintf(buffer, "Hi, %c%s%d", 'A', "World", -100);
  printf("%s\nCount = %d", buffer, count);

  return 0;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;  // Создаём объект для работы с аргументами
  va_start(args,
           format);  // Mакрос инициализирует переменную args

  char *start = str;

  while (*format != '\0') {
    if (*format != '%') {
      // Обычный символ - копируем в выходную строку
      *str++ = *format++;
      continue;
    }

    format++;  // Пропускаем '%'

    // Обработка %%
    if (*format == '%') {
      *str++ = *format++;
      continue;
    }

    // Обработка пробела
    if (*format == ' ') {
      *str++ = *format++;
    }

    // Парсинг спецификатора
    Format fmt;
    format = parse_format(format, &fmt);
    process_format(&fmt, args, &str);
  }

  *str = '\0';  // Завершаем строку
  va_end(args);  // Освобождает ресурсы, связанные с va_list
  return str - start;  // Количество записанных символов (без учёта '\0')
}

const char *parse_format(const char *fmt, Format *format) {
  init_format(format);
  const char *p = fmt;

  // Парсинг флагов
  while (*p == '-' || *p == '+' || *p == ' ' || *p == '0' || *p == '#') {
    if (*p == '-') {
      format->flags.minus = true;
      format->flags.zero = false;  // '-' отменяет '0'
    } else if (*p == '+') {
      format->flags.plus = true;
      format->flags.space = false;  // '+' отменяет пробел
    } else if (*p == ' ')
      format->flags.space = true;
    else if (*p == '0')
      format->flags.zero = true;
    else if (*p == '#')
      format->flags.hashtag = true;
    p++;
  }

  // Парсинг ширины
  if (*p == '*') {
    format->width.asterisk = true;
    p++;
  } else if (isdigit(*p)) {
    format->width.number = 0;
    while (isdigit(*p)) {
      format->width.number = format->width.number * 10 + (*p - '0');
      p++;
    }
  }

  // Парсинг точности
  if (*p == '*') {
    format->precision.asterisk = true;
    p++;
  } else if (*p == '.') {
    p++;
    format->precision.number = 0;
    while (isdigit(*p)) {
      format->precision.number = format->precision.number * 10 + (*p - '0');
      p++;
    }
  }

  // Парсинг модификаторов длины
  if (*p == 'h') {
    format->length.h = true;
    p++;
  } else if (*p == 'l') {
    format->length.l = true;
    p++;
  } else if (*p == 'L') {
    format->length.L = true;
    p++;
  }

  // Парсинг спецификатора
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
    case 'g':
      format->spec.g = true;
      break;
    case 'G':
      format->spec.G = true;
      break;
    case 'e':
      format->spec.e = true;
      break;
    case 'E':
      format->spec.E = true;
      break;
    case 'x':
      format->spec.x = true;
      break;
    case 'X':
      format->spec.X = true;
      break;
    case 'o':
      format->spec.o = true;
      break;
    case 'p':
      format->spec.p = true;
      break;
    case '%':
      format->spec.percent = true;
      break;
    default:
      // Неподдерживаемый спецификатор
      return fmt;
  }

  return p + 1;
}

void init_format(Format *format) {
  format->flags.minus = false;
  format->flags.plus = false;
  format->flags.space = false;
  format->flags.hashtag = false;
  format->flags.zero = false;

  format->width.number = 0;
  format->width.asterisk = false;

  format->precision.number = 0;
  format->precision.asterisk = false;

  format->length.h = false;
  format->length.l = false;
  format->length.L = false;

  format->spec.c = false;
  format->spec.d = false;
  format->spec.i = false;
  format->spec.e = false;
  format->spec.E = false;
  format->spec.f = false;
  format->spec.g = false;
  format->spec.G = false;
  format->spec.o = false;
  format->spec.s = false;
  format->spec.u = false;
  format->spec.x = false;
  format->spec.X = false;
  format->spec.p = false;
  format->spec.n = false;
  format->spec.percent = false;
}