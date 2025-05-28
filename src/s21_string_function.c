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

size_t s21_strlen(const char *str) {
    if (!str) {
        return 0;
    }
    unsigned int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

void *s21_to_upper(const char *str) {
    if (!str) {
        return S21_NULL;
    }
    // Вычисление длины строки
    size_t len = s21_strlen(str);

    // Выделение памяти под новую строку (+1 для нуль-терминатора)
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == S21_NULL) {
        return S21_NULL;
    }

    for (size_t i = 0; i <= len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            result[i] = str[i] - 32; // Переводим в верхний регистр
        } else {
            result[i] = str[i]; // Копируем без изменений
        }
    }
    return result;
}
