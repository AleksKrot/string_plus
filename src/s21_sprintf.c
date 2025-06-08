#include "s21_string_function.h"
#include "s21_sprintf.h"

#include <stdio.h>
#include <stdarg.h>

int s21_sprintf(char *str, const char *format, ...) {
    char str[256];
    int sym = 'c';
    Spec_form spec_form;
    init_struct(&spec_form);
    return 0;
}

void init_struct(Spec_form *spec_form) {
    spec_form->flag.minus = false;
    spec_form->flag.plus = false;
    spec_form->flag.space = false;
    spec_form->flag.hashtag = false;
    spec_form->flag.zero = false;

    spec_form->width.number = 0;
    spec_form->width.asterisk = false;

    spec_form->prec.number = 0;
    spec_form->prec.asterisk = false;

    spec_form->length.h = false;
    spec_form->length.l = false;
    spec_form->length.L = false;

    spec_form->spec.c = false;
    spec_form->spec.d = false;
    spec_form->spec.i = false;
    spec_form->spec.e = false;
    spec_form->spec.E = false;
    spec_form->spec.f = false;
    spec_form->spec.g = false;
    spec_form->spec.G = false;
    spec_form->spec.o = false;
    spec_form->spec.s = false;
    spec_form->spec.u = false;
    spec_form->spec.x = false;
    spec_form->spec.X = false;
    spec_form->spec.p = false;
    spec_form->spec.n = false;
    spec_form->spec.percent = false;
}

int input_function(Spec_form *spec_form, char *str, const char *format, ...) {
    int count = 0;
    
    while (*format != '\0') {
        if (*format != '%') {
            *str = *format;
            str++;
            format++;
            count++;
        } else {
            format++;
            if (*format == '%') {
                *str = *format;
                str++;
                format++;
                count++;
            } else {
                format = parsing_format(format, spec_form);
            }
        }
    }
    return count;
}

const char *parsing_flags(const char *ptr, Spec_form *spec_form) {
    if (*ptr == '-') {
        spec_form->flag.minus = true;
    } else if (*ptr == '+') {
        spec_form->flag.plus = true;
    } else if (*ptr == ' ') {
        spec_form->flag.space = true;
    } else if (*ptr == '#') {
        spec_form->flag.hashtag = true;
    } else if (*ptr == '0') {
        spec_form->flag.zero = true;
    } else {
        //TODO Написать ошибку
    }
    return ptr +  1;
}

const char *parsing_width(const char *ptr, Spec_form *spec_form) {
    if (isdigit(*ptr)) {
        spec_form->width.number = 0;
        while(isdigit(*ptr)) {
            spec_form->width.number = spec_form->width.number * 10 + (*ptr - '0');
            ptr++;
        }
    } else if (*ptr == '*') {
        spec_form->width.asterisk = true;
    } else {
        //TODO Написать ошибку
    }
    return ptr + 1;
}

const char *parsing_prec(const char *ptr, Spec_form *spec_form) {
    if (isdigit(*ptr)) {
        spec_form->prec.number = 0;
        while(isdigit(*ptr)) {
            spec_form->prec.number = spec_form->prec.number * 10 + (*ptr - '0');
            ptr++;
        }
    } else if (*ptr == '*') {
        spec_form->prec.asterisk = true;
    } else {
        //TODO Написать ошибку
    }
    return ptr + 1;
}

const char *parsing_spec(const char *ptr, Spec_form *spec_form) {
    if (*ptr == 'c') {
        spec_form->spec.c = true;
    } else if (*ptr == 'd') {
        spec_form->spec.d = true;
    } else if (*ptr == 'i') {
        spec_form->spec.i = true;
    } else if (*ptr == 'e') {
        spec_form->spec.e = true;
    } else if (*ptr == 'E') {
        spec_form->spec.E = true;
    } else if (*ptr == 'f') {
        spec_form->spec.f = true;
    } else if (*ptr == 'g') {
        spec_form->spec.g = true;
    } else if (*ptr == 'G') {
        spec_form->spec.G = true;
    } else if (*ptr == 'o') {
        spec_form->spec.o = true;
    } else if (*ptr == 's') {
        spec_form->spec.s = true;
    } else if (*ptr == 'u') {
        spec_form->spec.u = true;
    } else if (*ptr == 'x') {
        spec_form->spec.x = true;
    } else if (*ptr == 'X') {
        spec_form->spec.X = true;
    } else if (*ptr == 'p') {
        spec_form->spec.p = true;
    } else if (*ptr == 'n') {
        spec_form->spec.n = true;
    } else {
        //TODO Написать ошибку
    }
    return ptr + 1;
}

const char *parsing_format(const char *format, Spec_form *spec_form) {
    const char *ptr = format;
    ptr = parsing_flags(ptr, spec_form);
    if (*ptr != '.') {
        ptr = parsing_width(ptr, spec_form);
    } else {
        ptr++;
        ptr = parsing_prec(ptr, spec_form);
    }
    ptr = parsing_spec(ptr, spec_form);
    return ptr;
}