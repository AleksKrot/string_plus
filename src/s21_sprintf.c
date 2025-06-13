#include "s21_string.h"
#include "s21_sprintf.h"

#include <stdio.h>
#include <ctype.h>

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int count = 0;
    Spec_form spec_form = {0};
    
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
                processing_format(&spec_form, args);
                //writing_output();
            }
        }
    }

    va_end(args);
    return count;
}

const char *parsing_format(const char *format, Spec_form *spec_form) {
    const char *ptr = format;
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

void processing_format(Spec_form *spec_form, va_list args) {
    char temp[256] = {0}; // TODO Динамическая память
    int len = 0;

    process_spec(spec_form, args, temp, &len);
    // TODO Написать функции обрабтки формата
}

void process_spec(Spec_form *spec_form, va_list args, char *temp, int *len) {
    if (spec_form->spec.c) {
        spec_form->flag.plus = false;
        spec_form->flag.space = false;
        spec_form->prec.number = 0;
        spec_form->length.h = false;
        spec_form->length.l = false;
        
        char c = va_arg(args, int);

        int width = spec_form->width.number;

        if (width <= 1) {
            *(temp + *len) = c;
            (*len)++;
        } else {
            if (spec_form->flag.minus) {
                *(temp + *len) = c;
                (*len)++;
                for (int i = 1; i < width; i++) {
                    *(temp + *len) = ' ';
                    (*len)++;
                }
            } else {
                for (int i = 1; i < width; i++) {
                    *(temp + *len) = ' ';
                    (*len)++;
                }
                *(temp + *len) = c;
                (*len)++;
            }
        }
                
    } else if (spec_form->spec.d) {
        int d = va_arg(args, int);
        char buffer[32] = {0}; // TODO Динамическая память
        int pos = 0;
        if (d < 0) {
            *(buffer + pos) = '-';
            pos++;
            d = -d;
        } else if (spec_form->flag.plus) {
            spec_form->flag.space = false;
            *(buffer + pos) = '+';
            pos++;
        } else if (spec_form->flag.space) {
            *(buffer + pos) = ' ';
        }
        int start = pos;
        do {
            *(buffer + pos) = '0' + (d % 10);
            d = d / 10;
        } while (d > 0);
        int j = pos - 1;
        for (int i = start; i < j; i++) {
            char tmp = *(buffer + i);
            *(buffer + i) = *(buffer + j);
            *(buffer + j) = tmp;
            j--;
        }
        for (int i = 0; i < pos; i++) {
            *(temp + *len) = *(buffer + i);
            (*len)++;
        }
    }
}