#include "s21_string.h"

#include <stdarg.h>
static void s21_zero_flags(Flags *flags) {
  s21_memset(flags, 0, sizeof(Flags));
  flags->accuracy = -1;
}

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
    while (src[count] != '\0' && count < n) {
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

// изменение регистра на заглавные буквы
void *to_upper(const char *str) {
  char *copy_str = (char *)str;
  if (str != NULL) {
    size_t len = s21_strlen(str);
    for (size_t i = 0; i < len; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        copy_str[i] = str[i] - 32;
      }
    }
  }
  return copy_str;
}

// изменение регистра на строчные буквы
void *to_lower(const char *str) {
  char *copy_str = (char *)str;
  if (str != NULL) {
    size_t len = s21_strlen(str);
    for (size_t i = 0; i < len; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        copy_str[i] = str[i] + 32;
      }
    }
  }
  return copy_str;
}

static void s21_flags_int(char *result, char *str, char *prefix, Flags *flags) {
  if (result != NULL && str != NULL && prefix != NULL) {
    int count_space = 0;
    int count_zero = 0;
    if (!flags->alignment && flags->accuracy == -1 &&
        flags->width > s21_strlen(prefix) + s21_strlen(str) && flags->zero) {
      flags->accuracy = flags->width - s21_strlen(prefix);
    }
    count_zero = flags->accuracy - s21_strlen(str);
    if (count_zero > 0) {
      count_space =
          flags->width - count_zero - s21_strlen(str) - s21_strlen(prefix);
    } else {
      count_space = flags->width - s21_strlen(str) - s21_strlen(prefix);
    }

    if (!flags->alignment) {
      for (int i = 0; i < count_space; i++) {
        s21_strncat(result, " ", 1);
      }
    }
    s21_strncat(result, prefix, s21_strlen(prefix));
    for (int i = 0; i < count_zero; i++) {
      s21_strncat(result, "0", 1);
    }
    s21_strncat(result, str, s21_strlen(str));
    if (flags->alignment) {
      for (int i = 0; i < count_space; i++) {
        s21_strncat(result, " ", 1);
      }
    }
  }
}

// для %d, %i, %o, %u, %x
#define S21_ITS                                                                \
  if (result != NULL) {                                                        \
    char str[50] = "";                                                         \
    char prefix[3] = "";                                                       \
    int i = 0;                                                                 \
    if (num == 0 && flags->accuracy != 0) {                                    \
      str[0] = '0';                                                            \
      i++;                                                                     \
    }                                                                          \
    while (num != 0) {                                                         \
      int rem_num = num % num_sys;                                             \
      if (rem_num < 10) {                                                      \
        str[i] = (num % num_sys) + '0';                                        \
      } else {                                                                 \
        str[i] = (num % num_sys) - 10 + 'a';                                   \
      }                                                                        \
      num /= num_sys;                                                          \
      i++;                                                                     \
    }                                                                          \
    for (int j = 0; j < i / 2; j++) {                                          \
      char tmp = str[j];                                                       \
      str[j] = str[i - j - 1];                                                 \
      str[i - j - 1] = tmp;                                                    \
    }                                                                          \
    if (num_sys == 8 || num_sys == 16) {                                       \
      if (flags->sharp && num_sys == 8) {                                      \
        s21_strncat(prefix, "0", 1);                                           \
        if (flags->accuracy > 0) {                                             \
          flags->accuracy--;                                                   \
        }                                                                      \
      } else if (flags->sharp) {                                               \
        if (flags->accuracy > 1) {                                             \
          flags->accuracy -= 2;                                                \
        }                                                                      \
        s21_strncat(prefix, "0x", 2);                                          \
      }                                                                        \
    } else if (flags->is_negative) {                                           \
      s21_strncat(prefix, "-", 1);                                             \
    } else if (flags->sign) {                                                  \
      s21_strncat(prefix, "+", 1);                                             \
    } else if (flags->space) {                                                 \
      s21_strncat(prefix, " ", 1);                                             \
    }                                                                          \
    s21_flags_int(result, str, prefix, flags);                                 \
  }

void s21_int_to_str(char *result, long long int num, int num_sys,
                    Flags *flags) {
  if (num < 0) {
    num *= -1;
    flags->is_negative = true;
  }
  S21_ITS;
}

void s21_uint_to_str(char *result, unsigned long long int num, int num_sys,
                     Flags *flags) {
  S21_ITS;
}

static void s21_flags_float(char *result, char *str, char *prefix,
                            Flags *flags) {
  if (result != NULL && str != NULL && prefix != NULL) {
    int count_zero = 0;
    if (flags->zero) {
      count_zero = flags->width - s21_strlen(str) - s21_strlen(prefix);
    }
    int count_space =
        flags->width - s21_strlen(str) - s21_strlen(prefix) - count_zero;

    if (!flags->alignment) {
      for (int i = 0; i < count_space; i++) {
        s21_strncat(result, " ", 1);
      }
    }
    s21_strncat(result, prefix, s21_strlen(prefix));
    for (int i = 0; i < count_zero; i++) {
      s21_strncat(result, "0", 1);
    }
    s21_strncat(result, str, s21_strlen(str));
    if (flags->alignment) {
      for (int i = 0; i < count_space; i++) {
        s21_strncat(result, " ", 1);
      }
    }
  }
}
// для %f
void s21_float_to_str(char *result, long double num, Flags *flags) {
  if (result != NULL) {
    Flags int_flags;
    s21_zero_flags(&int_flags);
    char prefix[2] = "";
    char float_str[10000] = ""; // ИЗМЕНИТЬ!!!
    if (flags->sign && num >= 0) {
      s21_strncat(prefix, "+", 1);
    }
    if (num < 0) {
      num *= -1;
      s21_strncat(prefix, "-", 1);
    }
    long long int int_num = (int long long)num; // до точки
    s21_int_to_str(float_str, int_num, 10, &int_flags);
    s21_strncat(float_str, ".", 1);
    long double rem = num - int_num; // после точки
    int zero = 0; // подсчет количества нулей после .

    while (flags->accuracy > 0 && rem != 0.0) {
      rem *= 10;
      if (rem < 1.0) {
        s21_strncat(float_str, "0", 1);
        zero++;
      }
      flags->accuracy--;
    }
    long long int int_rem = (int long long)rem;
    while (zero != 0) {
      int_rem /= 10;
      rem /= 10;
      zero--;
    }
    long double round = rem - int_rem;
    if (round >= 0.5) {
      int_rem++;
    }
    s21_int_to_str(float_str, int_rem, 10, &int_flags);
    if (int_rem == 0) {
      for (int i = 0; i < flags->accuracy - 1; i++) {
        s21_strncat(float_str, "0", 1);
      }
    }
    s21_flags_float(result, float_str, prefix, flags);
  }
}

// для %e и %E
void s21_notat_float_to_str(char *result, long double num, Flags *flags) {
  if (result != NULL) {
    char prefix[2] = "";
    char float_str[1000] = ""; // ИЗМЕНИТЬ !!!!
    if (flags->sign && num >= 0) {
      s21_strncat(prefix, "+", 1);
    }
    if (num < 0) {
      num *= -1;
      s21_strncat(prefix, "-", 1);
    }
    int exp = 0;
    if (num >= 1.0) {
      while (num >= 10.0) {
        num /= 10;
        exp++;
      }
    } else {
      while (num < 1.0) {
        num *= 10;
        exp--;
      }
    }
    Flags float_flags;
    s21_zero_flags(&float_flags);
    float_flags.accuracy = flags->accuracy;
    s21_float_to_str(float_str, num, &float_flags);
    s21_strncat(float_str, "e", 1);
    if (exp < 0) {
      s21_strncat(float_str, "-", 1);
      exp *= -1;
    } else {
      s21_strncat(float_str, "+", 1);
    }
    if (exp < 10) {
      s21_strncat(float_str, "0", 1);
    }
    float_flags.accuracy = -1;
    s21_int_to_str(float_str, exp, 10, &float_flags);
    s21_flags_float(result, float_str, prefix, flags);
  }
}

// для g и G
void s21_g_float_to_str(char *result, float num, Flags *flags) {
  if (result != NULL) {
    size_t len0 = s21_strlen(result);
    s21_float_to_str(result, num, flags);
    size_t len1 = s21_strlen(result);
    result[len0] = '\0';
    s21_notat_float_to_str(result, num, flags);
    size_t len2 = s21_strlen(result);
    if (len1 < len2) {
      result[len0] = '\0';
      s21_float_to_str(result, num, flags);
    }
  }
}

// для %c
void s21_char_to_str(char *result, char c) {
  if (result != NULL) {
    char str[2] = "";
    str[0] = c;
    str[1] = '\0';
    s21_strncat(result, str, 1);
  }
}

// для %s
void s21_str_to_str(char *result, char *str, Flags *flags) {
  if (result != NULL && str != NULL) {
    if (flags->accuracy) {
      s21_strncat(result, str, flags->accuracy);
    } else {
      s21_strncat(result, str, s21_strlen(str));
    }
  }
}

void s21_ptr_to_str(char *result, void *ptr, Flags *flags) {
  if (result != NULL && ptr != NULL) {
    flags->sharp = true;
    s21_uint_to_str(result, (long long int)&ptr, 16, flags);
  }
}

static void s21_sprintf_flags(char c, Flags *flags) {
  switch (c) {
  case '-':
    flags->alignment = true;
    break;
  case '+':
    flags->sign = true;
    break;
  case ' ':
    flags->space = true;
    break;
  case '#':
    flags->sharp = true;
    break;
  case '0':
    flags->zero = true;
    break;
  }
  if (flags->alignment && flags->zero) {
    flags->zero = false;
  }
  if (flags->sign && flags->space) {
    flags->space = false;
  }
}

static int s21_sprintf_read_int(const char *str, int *i) {
  unsigned long long int ptr = 0;
  while (is_digit(str[*i])) {
    ptr *= 10;
    ptr += str[*i] - '0';
    (*i)++;
    if (ptr > INT_MAX) {
      ptr = (unsigned long long int)INT_MAX + 1;
    }
  }
  if (ptr > INT_MAX) {
    ptr = -1;
  }
  return ptr;
}

int s21_sprintf(char *str, const char *format, ...) {
  size_t len = s21_strlen(str);
  va_list factor;           // указатель va_list
  va_start(factor, format); // устанавливаем указатель
  int i = 0;
  int state = 0;
  size_t len_str = s21_strlen(str);
  Flags flags;
  s21_zero_flags(&flags);
  // %[флаги][ширина][.точность][длина]спецификатор.
  while (format[i] != '\0') {
    if (format[i] == '%') {
      s21_zero_flags(&flags);
      state = 1;
    } else if (is_flag(format[i]) && state > 0) {
      s21_sprintf_flags(format[i], &flags);
    } else if ((is_digit(format[i]) || format[i] == '*') && state == 1) {
      if (is_digit(format[i])) {
        flags.width = s21_sprintf_read_int(format, &i);
        i--;
      } else {
        flags.width = va_arg(factor, int);
      }
      state = 2;
    } else if (format[i] == '.' &&
               (is_digit(format[i + 1]) || format[i + 1] == '*') && state > 0 &&
               state < 3) {
      i++;
      if (is_digit(format[i])) {
        flags.accuracy = s21_sprintf_read_int(format, &i);
        i--;
      } else {
        flags.accuracy = va_arg(factor, int);
      }
      state = 3;
    } else if (is_length(format[i]) && state > 0 && state < 4) {
      flags.size = format[i];
      state = 4;
    } else if (is_specifier(format[i]) && state > 0) {
      if (s21_strchr("eEfgG", format[i]) && flags.accuracy == -1) {
        flags.accuracy = 6;
      }
      switch (format[i]) {
      case '%':
        s21_char_to_str(str, '%');
        break;
      case 'c':
        s21_char_to_str(str, va_arg(factor, int));
        break;
      case 's':
        s21_str_to_str(str, va_arg(factor, char *), &flags);
        break;
      case 'd':
      case 'i':
        s21_int_to_str(str, va_arg(factor, int), 10, &flags);
        break;
      case 'o':
        s21_int_to_str(str, va_arg(factor, unsigned int), 8, &flags);
        break;
      case 'X':
        flags.is_up = true;
        s21_int_to_str(str, va_arg(factor, unsigned int), 16, &flags);
        break;
      case 'x':
        s21_int_to_str(str, va_arg(factor, unsigned int), 16, &flags);
        break;
      case 'u':
        s21_int_to_str(str, va_arg(factor, unsigned int), 10, &flags);
        break;
      case 'E':
        flags.is_up = true;
        s21_notat_float_to_str(str, va_arg(factor, double), &flags);
        break;
      case 'e':
        s21_notat_float_to_str(str, va_arg(factor, double), &flags);
        break;
      case 'f':
        s21_float_to_str(str, va_arg(factor, double), &flags);
        break;
      case 'G':
        flags.is_up = true;
        s21_g_float_to_str(str, va_arg(factor, double), &flags);
        break;
      case 'g':
        s21_g_float_to_str(str, va_arg(factor, double), &flags);
        break;
      case 'p':
        // s21_ptr_to_str(str, va_arg(factor, int), &flags); // to-do void *
        break;
      case 'n':
        int *n = va_arg(factor, int *);
        *n = s21_strlen(str) - len_str;
        break;
      }
      state = 0;
    } else if (state == 0) {
      s21_strncat(str, &(format[i]), 1);
    } else {
      state = 0;
    }
    i++;
  }
  va_end(factor); // завершаем обработку параметров
  return s21_strlen(str) - len;
}