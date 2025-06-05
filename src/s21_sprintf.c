#include "s21_string_function.h"

#include <stdbool.h>

typedef struct {
    bool minus;
    bool plus;
    bool space;
    bool hashtag;
    bool zero;
} Flags;

typedef struct {
    int number;
    bool asterisk;
} Width;

typedef struct {
    int number;
    bool asterisk;
} Accuracy;

typedef struct {
    bool h;
    bool l;
    bool L;
} Length;

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
} Specifiers;

void init_struct(Flags *flag, Width *width, Accuracy *accur, Length *length, Specifiers *spec) {
    flag->minus = false;
    flag->plus = false;
    flag->space = false;
    flag->hashtag = false;
    flag->zero = false;

    width->number = 0;
    width->asterisk = false;

    accur->number = 0;
    accur->asterisk = false;

    length->h = false;
    length->l = false;
    length->L = false;

    spec->c = false;
    spec->d = false;
    spec->i = false;
    spec->e = false;
    spec->E = false;
    spec->f = false;
    spec->g = false;
    spec->G = false;
    spec->o = false;
    spec->s = false;
    spec->u = false;
    spec->x = false;
    spec->X = false;
    spec->p = false;
    spec->n = false;
    spec->percent = false;
}