#include "s21_string.h"

int is_space(char c) { return (c == ' ' || c == '\t' || c == '\n'); }

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_A_to_F(char c) { return (c >= 'A' && c <= 'F'); }

int is_a_to_f(char c) { return (c >= 'a' && c <= 'f'); }

void reset_options(spec *opt) {
  opt->suppress = 0;
  opt->width = 0;
  opt->length = NONE;
  opt->sign = 0;
  opt->null_buf = 0;
  opt->percent = 0;
  opt->read = 0;
}

void skip_spaces(char *buf, spec *opt) {
  while (is_space(buf[opt->iterStr])) {
    opt->iterStr += 1;
  }
}

int is_null(char c) { return (c == '\0') ? 1 : 0; }

long long int s21_ll_integer(char *buf, spec *opt, int base) {
  int sign = 1;
  long long int num = 0;
  int width;
  opt->withoutDigit = 1;
  if (opt->width == 0) {
    width = S21_MAX_LINT;
  } else {
    width = opt->width;
  }
  if (buf[opt->iterStr] == '-') {
    sign *= -1;
    opt->iterStr += 1;
    width--;
  } else if (buf[opt->iterStr] == '+') {
    opt->iterStr += 1;
    width--;
  }
  if (base == 0 || base == 16) {
    if (buf[opt->iterStr] == '0' &&
        (buf[opt->iterStr + 1] == 'x' || buf[opt->iterStr + 1] == 'X') &&
        width > 0) {
      opt->iterStr += 2;
      opt->read = 1;
      width -= 2;
      base = 16;
    }
  }
  if (base == 0 || base == 8) {
    if (buf[opt->iterStr] == '0' && width > 0) {
      opt->withoutDigit = 0;
      opt->iterStr += 1;
      opt->read = 1;
      width--;
      base = 8;
    }
  }
  if (base == 0) {
    base = 10;
  }
  if (base == 10) {
    while (is_digit(buf[opt->iterStr]) && width > 0) {
      opt->withoutDigit = 0;
      if (num > S21_MAX_LLINT / 10 ||
          (num == S21_MAX_LLINT / 10 &&
           buf[opt->iterStr] - 48 >= S21_MAX_LLINT % 10)) {
        if (opt->length == LONG_LONG || opt->length == LONG) {
          num = S21_MAX_LLINT;
          if (sign < 0) {
            num *= sign;
            num--;
            sign = 1;
          }
          opt->iterStr += 1;
          break;
        } else {
          if (sign < 0) {
            num = 0;
            sign = 1;
          } else {
            num = -1;
          }
          opt->iterStr += 1;
          break;
        }
      }
      num = num * 10 + (int)buf[opt->iterStr] - 48;
      width--;
      opt->read = 1;
      opt->iterStr += 1;
    }
  } else if (base == 8) {
    while (is_digit(buf[opt->iterStr]) && buf[opt->iterStr] < 56 && width > 0) {
      opt->withoutDigit = 0;
      if (num > S21_MAX_LLINT / 8 ||
          (num == S21_MAX_LLINT / 8 &&
           buf[opt->iterStr] - 48 >= S21_MAX_LLINT % 8)) {
        if (opt->length == LONG_LONG || opt->length == LONG) {
          num = S21_MAX_LLINT;
          if (sign < 0) {
            num *= sign;
            num--;
            sign = 1;
          }
          opt->iterStr += 1;
          break;
        } else {
          if (sign < 0) {
            num = 0;
            sign = 1;
          } else {
            num = -1;
          }
          opt->iterStr += 1;
          break;
        }
      }
      num = num * 8;
      num += buf[opt->iterStr] - 48;
      width--;
      opt->read = 1;
      opt->iterStr += 1;
    }
  } else if (base == 16) {
    while ((is_digit(buf[opt->iterStr]) || is_A_to_F(buf[opt->iterStr]) ||
            is_a_to_f(buf[opt->iterStr])) &&
           width > 0) {
      opt->withoutDigit = 0;
      if (num > S21_MAX_LLINT / 16) {
        if (opt->length == LONG_LONG || opt->length == LONG) {
          num = S21_MAX_LLINT;
          if (sign < 0) {
            num *= sign;
            num--;
            sign = 1;
          }
          opt->iterStr += 1;
          break;
        } else {
          if (sign < 0) {
            num = 0;
            sign = 1;
          } else {
            num = -1;
          }
          opt->iterStr += 1;
          break;
        }
      }
      num = num * 16;
      if (is_digit(buf[opt->iterStr])) {
        num += buf[opt->iterStr] - 48;
      } else if (is_A_to_F(buf[opt->iterStr])) {
        num += buf[opt->iterStr] - 55;
      } else {
        num += buf[opt->iterStr] - 87;
      }
      width--;
      opt->read = 1;
      opt->iterStr += 1;
    }
  }
  num *= sign;
  return num;
}

unsigned long long int s21_unsigned_ll_integer(char *buf, spec *opt, int base) {
  return (unsigned long long int)s21_ll_integer(buf, opt, base);
}

int options_integer(char *buf, spec *opt, int base, va_list *args) {
  int read = 0;
  skip_spaces(buf, opt);
  if (!is_null(buf[opt->iterStr])) {
    if (!opt->suppress) {
      if (!opt->sign) {
        if (opt->length == SHORT_SHORT) {
          *(signed char *)va_arg(*args, void *) =
              (signed char)s21_ll_integer(buf, opt, base);
        } else if (opt->length == SHORT_INT) {
          *(short int *)va_arg(*args, void *) =
              (short int)s21_ll_integer(buf, opt, base);
        } else if (opt->length == LONG) {
          *(long int *)va_arg(*args, void *) =
              (long int)s21_ll_integer(buf, opt, base);
        } else if (opt->length == LONG_LONG) {
          *(long long int *)va_arg(*args, void *) =
              (long long int)s21_ll_integer(buf, opt, base);
        } else {
          *(int *)va_arg(*args, void *) = (int)s21_ll_integer(buf, opt, base);
        }
      } else {
        if (opt->length == SHORT_SHORT) {
          *(unsigned char *)va_arg(*args, void *) =
              (unsigned char)s21_ll_integer(buf, opt, base);
        } else if (opt->length == SHORT_INT) {
          *(unsigned short int *)va_arg(*args, void *) =
              (short int)s21_unsigned_ll_integer(buf, opt, base);
        } else if (opt->length == LONG) {
          *(unsigned long int *)va_arg(*args, void *) =
              (long int)s21_unsigned_ll_integer(buf, opt, base);
        } else if (opt->length == LONG_LONG) {
          *(unsigned long long int *)va_arg(*args, void *) =
              (long long int)s21_unsigned_ll_integer(buf, opt, base);
        } else {
          *(unsigned int *)va_arg(*args, void *) =
              (int)s21_unsigned_ll_integer(buf, opt, base);
        }
      }
      if (opt->read == 1) {
        read = 1;
      }
    } else {
      s21_ll_integer(buf, opt, base);
    }
  } else if (is_null(buf[opt->iterStr]) && opt->null_read == 0) {
    read = -1;
    opt->null_buf = 1;
  }
  return read;
}

char s21_char(char *buf, spec *opt) {
  char chr = buf[opt->iterStr];
  opt->iterStr += 1;
  return chr;
}

int options_char(char *buf, spec *opt, va_list *args) {
  int read = 0;
  if (!is_null(buf[opt->iterStr])) {
    if (!opt->suppress) {
      if (opt->length == LONG) {
        *(wchar_t *)va_arg(*args, void *) = s21_char(buf, opt);
      } else {
        *(char *)va_arg(*args, char *) = s21_char(buf, opt);
      }
      read = 1;
    } else {
      s21_char(buf, opt);
    }
  } else if (is_null(buf[opt->iterStr]) && opt->null_read == 0) {
    opt->null_buf = 1;
    read = -1;
  }
  opt->read = read;
  return read;
}

int options_n(spec *opt, va_list *args) {
  int read = 0;
  if (!opt->suppress) {
    if (opt->length == SHORT_SHORT) {
      *(signed char *)va_arg(*args, void *) = (signed char)opt->iterStr;
    } else if (opt->length == SHORT_INT) {
      *(short int *)va_arg(*args, void *) = (short int)opt->iterStr;
    } else if (opt->length == LONG) {
      *(long int *)va_arg(*args, void *) = (long int)opt->iterStr;
    } else if (opt->length == LONG_LONG) {
      *(long long int *)va_arg(*args, void *) = (long long int)opt->iterStr;
    } else {
      *(int *)va_arg(*args, void *) = opt->iterStr;
    }
  }
  return read;
}

int options_pointer(char *buf, spec *opt, va_list *args) {
  int read = 0;
  skip_spaces(buf, opt);
  if (!is_null(buf[opt->iterStr])) {
    if (!opt->suppress) {
      *(void **)va_arg(*args, void **) = (void *)s21_ll_integer(buf, opt, 16);
      read = 1;
    } else {
      s21_ll_integer(buf, opt, 16);
    }
  } else if (is_null(buf[opt->iterStr]) && opt->null_read == 0) {
    read = -1;
    opt->null_buf = 1;
  }
  return read;
}

char *s21_str(char *buf, spec *opt) {
  static char str[N];
  int width, i = 0;
  if (opt->width == 0) {
    width = S21_MAX_LINT;
  } else {
    width = opt->width;
  }
  while (!is_space(buf[opt->iterStr]) && !is_null(buf[opt->iterStr]) &&
         width > 0) {
    str[i++] = buf[opt->iterStr];
    opt->read = 1;
    opt->iterStr += 1;
    width--;
  }
  str[i] = '\0';
  return str;
}

int options_str(char *buf, spec *opt, va_list *args) {
  int read = 0;
  skip_spaces(buf, opt);
  if (!is_null(buf[opt->iterStr])) {
    if (!opt->suppress) {
      s21_strcpy(va_arg(*args, char *), s21_str(buf, opt));
      if (opt->read == 1) {
        read = 1;
      }
    } else {
      s21_str(buf, opt);
    }
  } else if (is_null(buf[opt->iterStr]) && opt->null_read == 0) {
    opt->null_buf = 1;
    read = -1;
  }
  return read;
}

long double s21_long_double(char *buf, spec *opt) {
  int sign = 1;
  long double num = 0.0, n = 0.0;
  int count = 0;
  int width;
  if (opt->width == 0) {
    width = S21_MAX_LINT;
  } else {
    width = opt->width;
  }
  if (buf[opt->iterStr] == '-') {
    sign *= -1.0;
    opt->iterStr += 1;
    width--;
  } else if (buf[opt->iterStr] == '+') {
    opt->iterStr += 1;
    width--;
  }
  while (is_digit(buf[opt->iterStr]) && width > 0) {
    num = num * 10.0 + buf[opt->iterStr] - 48.0;
    opt->iterStr += 1;
    opt->read = 1;
    width--;
  }
  if (buf[opt->iterStr] == '.' && width > 0) {
    opt->iterStr += 1;
    width--;
  }
  while (is_digit(buf[opt->iterStr]) && width > 0) {
    num = num * 10.0 + buf[opt->iterStr] - 48.0;
    count++;
    opt->iterStr += 1;
    opt->read = 1;
    width--;
  }
  num /= powl(10.0, count);
  num *= sign;
  if ((buf[opt->iterStr] == 'i' || buf[opt->iterStr] == 'I') &&
      (buf[opt->iterStr + 1] == 'n' || buf[opt->iterStr + 1] == 'N') &&
      (buf[opt->iterStr + 2] == 'f' || buf[opt->iterStr + 2] == 'F')) {
    num = S21_INF;
    num *= sign;
    opt->iterStr += 3;
    opt->read = 1;
  } else if ((buf[opt->iterStr] == 'n' || buf[opt->iterStr] == 'N') &&
             (buf[opt->iterStr + 1] == 'a' || buf[opt->iterStr + 1] == 'A') &&
             (buf[opt->iterStr + 2] == 'n' || buf[opt->iterStr + 2] == 'N')) {
    num = S21_NAN;
    num *= sign;
    opt->iterStr += 3;
    opt->read = 1;
  } else if ((buf[opt->iterStr] == 'e' || buf[opt->iterStr] == 'E') &&
             width > 0) {
    opt->iterStr += 1;
    sign = 1.0;
    width--;
    if (buf[opt->iterStr] == '-') {
      sign *= -1;
      opt->iterStr += 1;
      width--;
    } else if (buf[opt->iterStr] == '+') {
      opt->iterStr += 1;
      width--;
    }
    if (buf[opt->iterStr] == '-' || buf[opt->iterStr] == '+' ||
        !is_digit(buf[opt->iterStr])) {
      opt->error = 1;
    } else {
      while (is_digit(buf[opt->iterStr]) && width > 0) {
        n = n * 10 + buf[opt->iterStr] - 48.0;
        opt->iterStr += 1;
        width--;
      }
      if (sign > 0) {
        num *= powl(10.0, n);
      } else {
        num /= powl(10.0, n);
      }
    }
  }
  return num;
}

int options_float(char *buf, spec *opt, va_list *args) {
  int read = 0;
  skip_spaces(buf, opt);
  if (!is_null(buf[opt->iterStr])) {
    if (!opt->suppress) {
      long double number = s21_long_double(buf, opt);
      if (opt->length == LONG) {
        *(double *)va_arg(*args, void *) = (double)number;
      } else if (opt->length == LONG_DOUBLE) {
        *(long double *)va_arg(*args, void *) = number;
      } else {
        *(float *)va_arg(*args, void *) = (float)number;
      }
      if (opt->read == 1) {
        read = 1;
      }
    } else {
      s21_long_double(buf, opt);
    }
  } else if (is_null(buf[opt->iterStr]) && opt->null_read == 0) {
    opt->null_buf = 1;
    read = -1;
  }
  return read;
}

int pars(char *buf, const char *format, spec *opt, va_list *args) {
  int read = 0, base = 0, width = 0;
  int iterFormat = 0;
  int lengthFormat = (int)s21_strlen(format);
  for (; iterFormat < lengthFormat; iterFormat++) {
    if (is_space(format[iterFormat])) {
      if (is_space(buf[opt->iterStr])) {
        skip_spaces(buf, opt);
        continue;
      }
    }
    while (format[iterFormat] == buf[opt->iterStr] && !opt->percent &&
           format[iterFormat] != '%') {
      opt->iterStr += 1;
      iterFormat++;
    }
    if ((iterFormat == lengthFormat - 1 && format[iterFormat] == '%')) {
      opt->error = 1;
      read = -1;
    }
    if (opt->error || opt->withoutDigit || opt->null_buf || opt->invalid) {
      return read;
    }
    switch (format[iterFormat]) {
      case '%':
        if (opt->percent) {
          if (format[iterFormat + 1] == '%') {
            if (buf[opt->iterStr] == '%') {
              iterFormat++;
              opt->iterStr++;
            }
          } else {
            opt->error = 1;
          }
        } else {
          opt->percent = 1;
        }
        continue;
      case '*':
        opt->suppress = 1;
        continue;
      case 'c':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        read += options_char(buf, opt, args);
        break;
      case 'd':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        base = 10;
        read += options_integer(buf, opt, base, args);
        break;
      case 'i':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        base = 0;
        read += options_integer(buf, opt, base, args);
        break;
      case 'o':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        base = 8;
        opt->sign = UNSIGNED;
        read += options_integer(buf, opt, base, args);
        break;
      case 'u':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        base = 10;
        opt->sign = UNSIGNED;
        read += options_integer(buf, opt, base, args);
        break;
      case 'x':
      case 'X':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        base = 16;
        opt->sign = UNSIGNED;
        read += options_integer(buf, opt, base, args);
        break;
      case 'n':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        read += options_n(opt, args);
        break;
      case 's':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        read += options_str(buf, opt, args);
        break;
      case 'p':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        read += options_pointer(buf, opt, args);
        break;
      case 'e':
      case 'E':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        read += options_float(buf, opt, args);
        break;
      case 'g':
      case 'G':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        read += options_float(buf, opt, args);
        break;
      case 'f':
        if (!opt->percent) {
          opt->error = 1;
          break;
        }
        read += options_float(buf, opt, args);
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        width = width * 10 + (int)format[iterFormat] - 48;
        opt->width = width;
        continue;
      case 'h':
        (opt->length == SHORT_INT) ? (opt->length = SHORT_SHORT)
                                   : (opt->length = SHORT_INT);
        continue;
      case 'l':
        (opt->length == LONG) ? (opt->length = LONG_LONG)
                              : (opt->length = LONG);
        continue;
      case 'L':
        opt->length = LONG_DOUBLE;
        continue;
      case ' ':
      case '\n':
      case '\t':
        if (opt->percent) {
          opt->error = 1;
        }
        continue;
      default:
        opt->invalid = 1;
        continue;
    }
    if (read != 0) {
      opt->null_read = 1;
    }
    width = 0;
    reset_options(opt);
  }
  return read;
}

int s21_sscanf(char *buf, const char *format, ...) {
  spec opt = {0};
  int read = 0;
  va_list args;
  va_start(args, format);
  read = pars(buf, format, &opt, &args);
  va_end(args);
  return read;
}