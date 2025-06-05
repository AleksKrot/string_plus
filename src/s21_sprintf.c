#include "s21_string_function.h"

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
} Accur;

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
    Accur accur;
    Length length;
    Spec spec;
} Format;


void init_struct(Format *format) {
    format->flag.minus = false;
    format->flag.plus = false;
    format->flag.space = false;
    format->flag.hashtag = false;
    format->flag.zero = false;

    format->width.number = 0;
    format->width.asterisk = false;

    format->accur.number = 0;
    format->accur.asterisk = false;

    format->length.h = false;
    format->length.l = false;
    format->length.L = false;

    format->spec.c = false;
    format->spec.d = false;
    format->spec.i = false;
    format->spec.e = false;
    format->spec.E = false;
    format->spec.f = false;
    format->spec.g = false;
    format->spec.G = false;
    format->spec.o = false;
    format->spec.s = false;
    format->spec.u = false;
    format->spec.x = false;
    format->spec.X = false;
    format->spec.p = false;
    format->spec.n = false;
    format->spec.percent = false;
}