#include "s21_string_function.h"
#include "s21_sprintf.h"

#include <stdio.h>
#include <stdarg.h>

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = input_function(str, format, args); // TODO Разобраться с count
    va_end(args);
    return count;
}

int input_function(char *str, const char *format, va_list args) {
    int count = 0;
    Spec_form spec_form;
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
                format = parsing_format(format, &spec_form);
                process_format(&spec_form, args, &str, &count);
            }
        }
    }
    return count;
}

const char *parsing_format(const char *format, Spec_form *spec_form) {
    const char *ptr = format;
    init_struct(spec_form);
    ptr = parsing_flags(ptr, spec_form);
    if (isdigit(*ptr) || *ptr == '*') {
        ptr = parsing_width(ptr, spec_form);
    }
    if (*ptr == '.') {
        ptr++;
        ptr = parsing_prec(ptr, spec_form);
    }
    if (*ptr == 'h' || *ptr == 'l' || *ptr == 'L') {
        ptr = parsing_length(ptr, spec_form);
    }
    if (*ptr != '\0') {
        ptr = parsing_spec(ptr, spec_form);
    } // TODO Разобраться с возможными ошибками
    return ptr;
}

void init_struct(Spec_form *spec_form) { // TODO Рассмотреть возможность сокращения за счет составного литерата
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

const char *parsing_flags(const char *ptr, Spec_form *spec_form) {
    while (*ptr == '-' || *ptr == '+' || *ptr == ' ' || *ptr == '#' || *ptr == '0') {
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
        } //TODO Написать ошибку
        ptr++;
    }
    return ptr;
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
        ptr++;
    } else {
        //TODO Написать ошибку
    }
    return ptr;
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
        ptr++;
    } else {
        //TODO Написать ошибку и рассмотреть случай отрицательной ширины
    }
    return ptr;
}

const char *parsing_length(const char *ptr, Spec_form *spec_form) {
    if (*ptr == 'h') {
        spec_form->length.h = true;
        ptr++;
    } else if (*ptr == 'l') {
        spec_form->length.l = true;
        ptr++;
    } else if (*ptr == 'L') {
        spec_form->length.L = true;
        ptr++;
    } else {
        //TODO Написать ошибку
    }
    return ptr;
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
    } else if (*ptr == '%') {
        spec_form->spec.percent = true;
    } else {
        //TODO Написать ошибку и разобраться с ptr при ошибке
    }
    return ptr + 1;
}

void process_format(Spec_form *spec_form, va_list args, char **str, int *count) {
    char temp[256] = {0};
    int len = 0;

    process_spec(spec_form, args, temp, &len);

    /*if (spec_form->flag.minus || spec_form->flag.plus || spec_form->flag.space || spec_form->flag.hashtag || spec_form->flag.zero) {
        process_flag(spec_form, &str, &count);
    }*/

    // TODO Написать функции обрабтки формата
    for (int i = 0; i < len; i++) {
        **str = *(temp + i);
        (*str)++;
        (*count)++;
    }
}

void process_spec(Spec_form *spec_form, va_list args, char *temp, int *len) {
    if (spec_form->spec.c) {
        spec_form->flag.plus = false;
        spec_form->flag.space = false;
        spec_form->prec.number = 0;
        spec_form->length.h = false;
        spec_form->length.l = false;
        char c = va_arg(args, int);
        *(temp + *len) = c;
        (*len)++;
    }
}

/*void process_flag(Spec_form *spec_form, char **str, int *count) {
    if (spec_form->flag.minus) {

    }
}*/