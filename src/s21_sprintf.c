#include "s21_sprintf.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>  // Предназначена для работы с функциями с переменным числом аргументов
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "s21_string.h"

int main() {
  Format format;
  init_format(&format);

  char buffer[256];
  int count = sprintf(buffer, "Hi, %5c=%05d", 'A', -100);
  printf("%s\nCount = %d", buffer, count);

  return 0;
}

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

  // Parse flags
  while (*p == '-' || *p == '+' || *p == ' ') {
    if (*p == '-')
      format->flags.minus = true;
    else if (*p == '+')
      format->flags.plus = true;
    else if (*p == ' ')
      format->flags.space = true;
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
    format->precision.number = 0;
    while (isdigit(*p)) {
      format->precision.number = format->precision.number * 10 + (*p - '0');
      p++;
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

  if (format->spec.c) {
    char c = (char)va_arg(args, int);
    *ptr++ = c;
  } else if (format->spec.d) {
    long num = format->length.l ? va_arg(args, long) : va_arg(args, int);
    if (format->length.h) num = (short)num;

    char num_str[32];
    sprintf(num_str, "%ld", labs(num));

    if (num < 0)
      *ptr++ = '-';
    else if (format->flags.plus)
      *ptr++ = '+';
    else if (format->flags.space)
      *ptr++ = ' ';

    strcpy(ptr, num_str);
    ptr += strlen(num_str);
  } else if (format->spec.f) {
    double num = format->length.l ? va_arg(args, double) : va_arg(args, double);

    char format_str[16];
    sprintf(format_str, "%%.%df", format->precision.number);

    char num_str[64];
    sprintf(num_str, format_str, fabs(num));

    if (num < 0)
      *ptr++ = '-';
    else if (format->flags.plus)
      *ptr++ = '+';
    else if (format->flags.space)
      *ptr++ = ' ';

    strcpy(ptr, num_str);
    ptr += strlen(num_str);
  } else if (format->spec.s) {
    char *s = va_arg(args, char *);
    int max_len =
        format->precision.number > 0 ? format->precision.number : strlen(s);
    strncpy(ptr, s, max_len);
    ptr += max_len;
  } else if (format->spec.u) {
    unsigned long num = format->length.l ? va_arg(args, unsigned long)
                                         : va_arg(args, unsigned int);
    if (format->length.h) num = (unsigned short)num;

    char num_str[32];
    sprintf(num_str, "%lu", num);
    strcpy(ptr, num_str);
    ptr += strlen(num_str);
  } else if (format->spec.percent) {
    *ptr++ = '%';
  }

  // Apply width
  int len = ptr - temp;
  if (format->width.number > len) {
    int padding = format->width.number - len;

    if (format->flags.minus) {
      // Left-align with spaces on right
      memset(ptr, ' ', padding);
      ptr += padding;
    } else {
      // Right-align with spaces or zeros on left
      char pad_char = ' ';
      memmove(temp + padding, temp, len);
      memset(temp, pad_char, padding);
      ptr += padding;
    }
  }

  // Copy to output buffer
  int total = ptr - temp;
  memcpy(*buffer, temp, total);
  *buffer += total;
}
