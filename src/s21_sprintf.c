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