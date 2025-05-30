#include "s21_string_function.h"

#include <stdio.h>

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *result = S21_NULL;
    const unsigned char *s = str;
    for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
        if (*(s + i) == (unsigned char)c) {
            result = (void *)(s + i);
        } 
    }
    return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int result = 0;
    const char *s1 = str1;
    const char *s2 = str2;

    for (s21_size_t i = 0; i < n && result == 0; i++) {
        if (*(s1 + i) != *(s2 + i)) {
            result = *(s1 + i) - *(s2 + i);
        }
    }
    return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    char *d = dest;
    const char *s = src;
    for (s21_size_t i = 0; i < n; i++) {
        *(d + i) = *(s + i);
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    char *s = str;
    for (s21_size_t i = 0; i < n; i++) {
        *(s + i) = (unsigned char)c;
    }
    return s;
}

s21_size_t s21_strlen(const char *str)
{
    s21_size_t len = 0;
    while (*(str + len) != '\0') {
        len++;
    }
    return len;
} 
