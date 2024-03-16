#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_SIZE_T n) {
  unsigned char *buff = (unsigned char *)str;
  unsigned char *res = s21_NULL;
  for (s21_SIZE_T i = 0; i < n; i++) {
    if (buff[i] == c) {
      res = &buff[i];
      i = i + n;
    }
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_SIZE_T n) {
  int count = 0;
  if (str1 != s21_NULL && str2 != s21_NULL) {
    unsigned char *buff1 = (unsigned char *)str1;
    unsigned char *buff2 = (unsigned char *)str2;
    for (s21_SIZE_T i = 0; i < n; i++) {
      if (buff1[i] != buff2[i]) {
        count = (int)(buff1[i] - buff2[i]);
        break;
      }
    }
  }
  return count;
}

void *s21_memcpy(void *dest, const void *str, s21_SIZE_T n) {
  if (dest != s21_NULL && str != s21_NULL) {
    unsigned char *buff1 = (unsigned char *)dest;
    unsigned char *buff2 = (unsigned char *)str;
    for (s21_SIZE_T i = 0; i < n; i++) {
      buff1[i] = buff2[i];
    }
  }
  return dest;
}

void *s21_memmove(void *dest, const void *str, s21_SIZE_T n) {
  if (dest != s21_NULL && str != s21_NULL) {
    unsigned char *buff1 = (unsigned char *)dest;
    unsigned char *buff2 = (unsigned char *)str;
    if (dest < str) {
      for (s21_SIZE_T i = 0; i < n; i++) {
        buff1[i] = buff2[i];
      }
    } else {
      for (s21_SIZE_T i = n; i > 0; i--) {
        buff1[i - 1] = buff2[i - 1];
      }
    }
  }
  return dest;
}

void *s21_memset(void *str, int ch, s21_SIZE_T n) {
  unsigned char *buff = (unsigned char *)str;
  if (str != s21_NULL) {
    for (s21_SIZE_T i = 0; i < n; i++) {
      buff[i] = ch;
    }
  }
  return buff;
}

char *s21_strcat(char *dest, const char *src) {
  int i = 0;
  while (dest[i] != '\0') {
    i++;
  }
  int n = 0;
  while (src[n] != '\0') {
    n++;
  }
  for (int c = 0; c < n + 1; c++, i++) {
    dest[i] = src[c];
  }
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_SIZE_T n) {
  int max = n;
  int i = 0;
  while (dest[i] != '\0') {
    i++;
  }
  int k = 0;
  while (src[k] != '\0' && k != max - 1) {
    k++;
  }
  for (int c = 0; c <= k; c++, i++) {
    dest[i] = src[c];
  }
  dest[i + 1] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  int check = 0;
  while (str[i] != '\0') {
    if (str[i] == c) {
      check = 1;
      break;
    } else {
      i++;
    }
  }
  if (check == 1) {
    return (char *)&str[i];
  } else {
    return s21_NULL;
  }
}

int s21_strcmp(const char *str1, const char *str2) {
  int i = 0;
  int res1 = 0;
  int res2 = 0;
  while (1) {
    if (str1[i] != str2[i]) {
      res1 = str1[i];
      res2 = str2[i];
      break;
    }
    if (str1[i] == '\0' || str2[i] == '\0') {
      res1 = str1[i];
      res2 = str2[i];
      break;
    }
    i++;
  }
  return res1 - res2;
}

int s21_strncmp(const char *str1, const char *str2, s21_SIZE_T n) {
  int i = 0;
  int size = n;
  int res1 = 0;
  int res2 = 0;
  while (i < size) {
    if (str1[i] != str2[i]) {
      res1 = str1[i];
      res2 = str2[i];
      break;
    }
    if (str1[i] == '\0' || str2[i] == '\0') {
      res1 = str1[i];
      res2 = str2[i];
      break;
    }
    i++;
  }
  return res1 - res2;
}

char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  for (; src[i] != '\0'; i++) dest[i] = src[i];
  dest[i] = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_SIZE_T n) {
  int i = 0, j = 0;
  for (; i < (int)n; i++) {
    if (j == 0) dest[i] = src[i];
    if (j == 1) dest[i] = '\0';
    if (src[i] == '\0') j = 1;
  }
  return dest;
}

s21_SIZE_T s21_strcspn(const char *str1, const char *str2) {
  s21_SIZE_T i = 0;
  while (str1[i] != '\0') {
    int j = 0;
    while (str2[j] != '\0') {
      if (str1[i] != str2[j]) {
        j++;
      } else {
        break;
      }
    }
    if (str1[i] == str2[j]) break;
    i++;
  }
  return i;
}

char *s21_strerror(int errnum) {
  static char result[1000] = {'\0'};
  static char number[100] = {'\0'};
  if (errnum >= 0 && errnum <= MAX_ERROR - 1) {
    char *errors[] = MASS_ERROR;
    s21_strcpy(result, errors[errnum]);
  } else {
    if (MAX_ERROR == 107) s21_strcpy(result, "Unknown error: ");
    if (MAX_ERROR == 134) s21_strcpy(result, "Unknown error ");
    s21_itoc(errnum, number);
    s21_strcat(result, number);
  }
  return result;
}

void s21_itoc(int number, char *result) {
  char gnistr[SIZE] = {'\0'};
  int minus = number < 0;
  if (minus) number = -number;
  int i = 0;
  for (i = 0; number > 0; i++) {
    gnistr[i] = (number % 10) + 48;
    number /= 10;
  }
  if (minus) gnistr[i++] = '-';

  int len = (int)s21_strlen(gnistr);
  for (i = 0; i < len; i++) {
    result[i] = gnistr[len - i - 1];
    result[i + 1] = '\0';
  }
}

s21_SIZE_T s21_strlen(const char *str) {
  s21_SIZE_T rezult = 0;
  for (; str[rezult] != '\0'; rezult++)
    ;
  return rezult;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  int i = 0;
  const char *result = s21_NULL;
  while (str1[i] != '\0') {
    int j = 0;
    while (str2[j] != '\0') {
      if (str1[i] != str2[j]) {
        j++;
      } else {
        break;
      }
    }
    if (str1[i] == str2[j]) break;
    i++;
  }
  if (str1[i] != '\0') result = str1 + i;
  return (char *)result;
}

char *s21_strrchr(const char *str, int c) {
  int i = 0;
  const char *result = s21_NULL;
  while (str[i] != '\0') {
    if (str[i] == (char)c) result = str + i;
    i++;
  }
  if (c == '\0') result = str + i;
  return (char *)result;
}

s21_SIZE_T s21_strspn(const char *str1, const char *str2) {
  int i = 0, resBuf = -1;
  s21_SIZE_T result = 0;
  while (str1[i] != '\0' && resBuf != (int)result) {
    int j = 0;
    resBuf = result;
    while (str2[j] != '\0') {
      if (str1[i] != str2[j]) {
        j++;
      } else {
        result++;
        break;
      }
    }
    i++;
  }
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  if (s21_strlen(haystack) >= s21_strlen(needle)) {
    for (int i = 0; i <= (int)s21_strlen(haystack) - (int)s21_strlen(needle);
         i++) {
      int check = 1;
      for (int j = i, k = 0; needle[k]; k++, j++) {
        if (haystack[j] != needle[k]) {
          check = 0;
          break;
        }
      }
      if (check) {
        result = (char *)haystack + i;
        break;
      }
    }
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *staticTime = s21_NULL;
  char *time = s21_NULL, *result = s21_NULL;
  if (str) {
    int i = 0;
    i = s21_strspn(str, delim);
    str = str + i;
    time = s21_strpbrk(str, delim);
    if (time != s21_NULL) {
      time[0] = '\0';
      staticTime = time + 1;
      result = str;
    } else {
      result = str;
      staticTime = s21_NULL;
    }
  } else {
    if (staticTime != s21_NULL) {
      time = s21_strpbrk(staticTime, delim);
      if (time != s21_NULL) {
        time[0] = '\0';
        result = staticTime;
        staticTime = time + 1;
      } else {
        result = staticTime;
        staticTime = s21_NULL;
      }
    } else {
      result = s21_NULL;
    }
  }
  return result;
}

void *s21_to_upper(const char *str) {
  if (!str) return s21_NULL;
  char *result;
  result = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    result[i] = str[i];
  }
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    if (str[i] >= 97 && str[i] <= 122) {
      result[i] = result[i] - 32;
    }
  }
  return (void *)result;
}

void *s21_to_lower(const char *str) {
  if (!str) return s21_NULL;
  char *result;
  result = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    result[i] = str[i];
  }
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      result[i] = result[i] + 32;
    }
  }
  return (void *)result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) return s21_NULL;
  char *result;
  result = (char *)calloc(s21_strlen(src) + 1, sizeof(char));
  int start = 0, end = (int)s21_strlen(src);
  int tc = (!(!trim_chars || (s21_strlen(trim_chars)) == 0));
  int total = 0;

  for (int i = 0; i < (int)s21_strlen(src); i++) {
    int flag = 1;
    if (tc && (s21_strchr(trim_chars, src[i]) != NULL))
      flag = 0;
    else if (!tc && (s21_strchr(" \f\n\r\t\v", src[i]) != NULL))
      flag = 0;
    if (flag) {
      start = i;
      total += 1;
      break;
    }
  }

  for (int i = end - 1; i >= 0; i--) {
    int flag = 1;
    if (tc && (s21_strchr(trim_chars, src[i]) != NULL))
      flag = 0;
    else if (!tc && (s21_strchr(" \f\n\r\t\v", src[i]) != NULL))
      flag = 0;
    if (flag) {
      end = i + 1;
      total += 1;
      break;
    }
  }

  if (total)
    for (int i = start; i < end; i++) {
      result[i - start] = src[i];
      result[i - start + 1] = '\0';
    }
  else
    result[0] = '\0';

  return (void *)result;
}

void *s21_insert(const char *src, const char *str, s21_SIZE_T start_index) {
  if (!src || start_index > s21_strlen(src)) {
    return s21_NULL;
  }
  if (!str) str = "";
  char *res;
  res = (char *)calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
  for (int i = 0; i < (int)start_index; i++) {
    res[i] = src[i];
  }
  int new_index = start_index;
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    res[new_index++] = str[i];
  }
  for (int i = new_index; src[start_index] != '\0'; i++, start_index++) {
    res[i] = src[start_index];
  }
  return (void *)res;
}
