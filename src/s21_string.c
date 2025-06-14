#include "s21_string.h"


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
    unsigned char *s = str;
    
    for (s21_size_t i = 0; i < n; i++) {
        *(s + i) = (unsigned char)c;
    }

    return s;
}

s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;

    while (*(str + len) != '\0') {
        len++;
    }

    return len;
} 

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *d = dest;
    char *d_finish = d + s21_strlen(d);
    const char *s = src;
    
    for (s21_size_t i = 0; i < n; i++) {
        *(d_finish + i) = *(s + i);
    }

    return d;
}

char *s21_strchr(const char *str, int c) {
    const char *s = str;
    void *result = S21_NULL;
    int i = 0;
    
    while (*(s + i) != '\0' && result == S21_NULL) {
        if (*(s + i) == (unsigned char)c) {
            result = (char *)(s + i);
        }
        i++;
    }

    if (c == '\0') {
        result = (char *)s + i;
    }

    return result;
}

char *s21_strrchr(const char *str, int c) {
    const char *s = str;
    void *result = S21_NULL;
    int i = 0;

    while (*(s + i) != '\0') {
        if (*(s + i) == (unsigned char)c) {
            result = (char *)(s + i);
        }
        i++;
    }

    if (c == '\0') {
        result = (char *)s + i;
    }

    return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int result = 0;
    const char *s1 = str1;
    const char *s2 = str2;

    for (s21_size_t i = 0; i < n; i++) {
        if (*(s1 + i) != *(s2 + i)) {
            result = *(s1 + i) - *(s2 + i);
            i = n;
        }
    }

    return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char *d = dest;
    const char *s = src;

    for (s21_size_t i = 0; i < n; i++) {
        *(d + i) = *(s + i);
    }

    return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t result = 0;

    s21_size_t len = 0;
    while (*(str1 + len)) {
        len++;
    }
    result = len;

    for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
        for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
            if (*(str1 + i) == *(str2 + j)) {
                result = i;
                i = s21_strlen(str1);
            }
        }
    }

    return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    void *result = S21_NULL;

    for (s21_size_t i = 0; i < s21_strlen(str1) && result == S21_NULL; i++) {
        for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
            if (*(str1 + i) == *(str2 + j)) {
                result = (void *)(str1 + i);
            }
        }
    }

    return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *result = S21_NULL;

    if (*needle == '\0') {
        result = (char *)haystack;
    }

    while (*haystack != '\0' && result == S21_NULL) {
        const char *h = haystack;
        const char *n = needle;
        while (*n != '\0' && *h == *n) {
            n++;
            h++;
        }
        if (*n == '\0') {
            result = (char *) haystack;
        }
        haystack++;
    }

    return result;
}

char *s21_strtok(char *str, const char *delim) {
    char *last = S21_NULL;
    char *result = S21_NULL;
    if (str != S21_NULL) {
        last = str;
    }
    if (last == S21_NULL || *last == '\0') {
        result = S21_NULL;
    }
    while (*last != '\0' && *last == *delim) {
        last++;
    }
    if (*last == '\0') {
        result = S21_NULL;
    }
    result = last;
    while (*last != '\0' && *last != *delim) {
        last++;
    }
    if (*last == *delim) {
        *last = '\0';
        last++;
    }
    return result;
}