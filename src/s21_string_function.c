#include "s21_string_function.h"

#include <stdio.h>

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *result = S21_NULL;
    const unsigned char *s = str;
    for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
        if (s[i] == (unsigned char)c) {
            result = (void *)(s + i);
        } 
    }
    return result;
}
