#ifndef S21_SPRINTF_H  
#define S21_SPRINTF_H

#include <stdbool.h>

// Структура для хранения флагов
typedef struct {
    bool minus;
    bool plus;
    bool space;
    bool hashtag;
    bool zero;
} Flags;

// Структура для хранения ширины
typedef struct {
    int number;
    bool asterisk;
} Width;

// Структура для хранения точности
typedef struct {
    int number;
    bool asterisk;
} Prec;

// Структура для хранения длины
typedef struct {
    bool h;
    bool l;
    bool L;
} Length;

// Структура для хранения спецификаторов
typedef struct {
    bool c;
    bool d;
    bool i;
    bool e;
    bool E;
    bool f;
    bool g;
    bool G;
    bool o;
    bool s;
    bool u;
    bool x;
    bool X;
    bool p;
    bool n;
    bool percent;
} Spec;

// Структура описывающая форматированный вывод
typedef struct {
    Flags flag;
    Width width;
    Prec prec;
    Length length;
    Spec spec;
} Spec_form;

// Функция для форматирования вывода в строку
int s21_sprintf(char *str, const char *format, ...);

// Функция ввода
int input_function(Spec_form *spec_form, char *str, const char *format, ...);

// Инициализация структуры
void init_struct(Spec_form *spec_form);

// Парсер флагов
const char *parsing_flags(const char *ptr, Spec_form *spec_form);

// Парсер спецификатора
const char *parsing_spec(const char *ptr, Spec_form *spec_form);

// Парсер спецификатора формата
const char *parsing_format(const char *format, Spec_form *spec_form);

#endif