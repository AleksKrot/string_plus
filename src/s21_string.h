#ifndef S21_STRING_H
#define S21_STRING_H

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define S21_NULL ((void *)0)

typedef unsigned long s21_size_t;

// Функция выполняет поиск первого вхождения символа c в первых n байтах строки,
// на которую указывает аргумент str
void *s21_memchr(const void *str, int c, s21_size_t n);

// Функция cравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

// Функция копирует n символов из источника в место назначения
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

// Функция копирует символ c (беззнаковый символ) в первые n символов строки, на
// которую указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n);

// Функция добавляет строку, на которую указывает src, в конец строки, на
// которую указывает dest, длиной до n символов
char *s21_strncat(char *dest, const char *src, s21_size_t n);

// Функция выполняет поиск первого вхождения символа c в строке, на которую
// указывает аргумент str.
char *s21_strchr(const char *str, int c);

// Функция сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

// Функция для копирование строки
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

// Функция для набора символов в строке
s21_size_t s21_strcspn(const char *str1, const char *str2);

// Функция для возврата строки, описывающую ошибку
char *s21_strerror(int errnum);

// Функция для вычисления длины строки без учета '\0'
s21_size_t s21_strlen(const char *str);

// Функция для поиска строки для любого набора символов
char *s21_strpbrk(const char *str1, const char *str2);

// Функция для определения местонахождения символа в строке
char *s21_strrchr(const char *str, int c);

// Функция для нахождения подстроки
char *s21_strstr(const char *haystack, const char *needle);

// Функция для извлечения токенов из строки
char *s21_strtok(char *str, const char *delim);

// Функция для ввода с преобразованием формата
int s21_sscanf(const char *str, const char *format, ...);

// Функция для вывода данных с преобразованием формата
int s21_sprintf(char *str, const char *format, ...);

// Функция для преобразования символов в верхний регистр
void *s21_to_upper(const char *str);

// Функция для преобразования символов в нижний регистр
void *s21_to_lower(const char *str);

// Функция для вставки строки
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

// Функция для удаления всех начальных и конечных вхождений символов из строки
void *s21_trim(const char *src, const char *trim_chars);

#endif