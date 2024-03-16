#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list ptr;
  va_start(ptr, format);

  int i = 0;
  int count = 0;

  while (format[i] != '\0') {
    if (format[i] == '%') {
      ParserString parser = {0};

      int n = 1;
      i++;

      while (format[i] == '-' || format[i] == '+' || format[i] == ' ' ||
             format[i] == '#' || format[i] == '0') {
        switch (format[i]) {
          case '-':
            parser.minus = 1;
            i++;
            break;
          case '+':
            parser.plus = 1;
            i++;
            break;
          case ' ':
            parser.space = 1;
            i++;
            break;
          case '#':
            parser.grill = 1;
            i++;
            break;
          case '0':
            parser.zero = 1;
            i++;
            break;
        }
      }

      if (format[i] == '*') {
        int zvezda = 0;
        zvezda = va_arg(ptr, int);
        if (zvezda > 0) {
          parser.minNum = zvezda;
        }
        i++;
      } else {
        while (format[i] >= 48 && format[i] <= 57) {
          parser.minNum = parser.minNum * n;
          parser.minNum = parser.minNum + (format[i] - 48);
          n = 10;
          i++;
        }
      }

      if (format[i] == '.') {
        i++;
        if (format[i] == '*') {
          int zvezdaFractional = 0;
          zvezdaFractional = va_arg(ptr, int);
          if (zvezdaFractional >= 0) {
            parser.fractionalMinNum = zvezdaFractional;
          }
          i++;
        } else {
          int m = 1;
          while (format[i] >= 48 && format[i] <= 57) {
            parser.fractionalMinNum =
                parser.fractionalMinNum * m + (format[i] - 48);
            m = 10;
            i++;
          }
        }
        if (parser.fractionalMinNum == 0 || parser.fractionalMinNum == '\0') {
          parser.fractionalZero = 1;
        }
      }

      switch (format[i]) {
        case 'h':
          parser.length = 'h';
          i++;
          break;
        case 'L':
          parser.length = 'L';
          i++;
          break;
        case 'l':
          parser.length = 'l';
          i++;
          break;
      }

      switch (format[i]) {
        case 'c':
          parser.specifier = 'c';
          int WideC = 0;
          if (parser.length == 'l') {
            WideSymbol(va_arg(ptr, wchar_t), &WideC);
          } else {
            WideC = va_arg(ptr, int);
          }
          flag_c(WideC, &parser);
          i++;
          break;
        case 'd':
          parser.specifier = 'd';
          if (parser.length == 'l') {
            flag_d(va_arg(ptr, long int), &parser);
          } else {
            flag_d(va_arg(ptr, int), &parser);
          }
          i++;
          break;
        case 'i':
          parser.specifier = 'i';
          if (parser.length == 'l') {
            flag_d(va_arg(ptr, long int), &parser);
          } else {
            flag_d(va_arg(ptr, int), &parser);
          }
          i++;
          break;
        case 'f':
          parser.specifier = 'f';
          if (parser.length == 'L') {
            flag_f(va_arg(ptr, long double), &parser);
          } else {
            flag_f(va_arg(ptr, double), &parser);
          }
          i++;
          break;
        case 's':
          parser.specifier = 's';
          char WideBuffer[4096] = {0};
          if (parser.length == 'l') {
            WideCharacter(va_arg(ptr, wchar_t *), WideBuffer);
            flag_s(WideBuffer, &parser);
          } else {
            char *abc = va_arg(ptr, char *);
            if (abc == NULL) {
              char WideBuffer2[4096] = "(null)\0";
              flag_s(WideBuffer2, &parser);
            } else {
              flag_s(abc, &parser);
            }
          }
          i++;
          break;
        case 'u':
          parser.specifier = 'u';
          if (parser.length == 'l') {
            flag_d((long int)va_arg(ptr, unsigned long int), &parser);
          } else {
            flag_d((long int)va_arg(ptr, unsigned int), &parser);
          }
          i++;
          break;
        case '%':
          parser.specifier = '%';
          parser.mass[0] = '%';
          i++;
          break;
        case 'g':
          parser.specifier = 'g';
          if (parser.length == 'L') {
            flag_gG((long double)va_arg(ptr, long double), &parser);
          } else {
            flag_gG((long double)va_arg(ptr, double), &parser);
          }
          i++;
          break;
        case 'G':
          parser.specifier = 'G';
          if (parser.length == 'L') {
            flag_gG((long double)va_arg(ptr, long double), &parser);
          } else {
            flag_gG((long double)va_arg(ptr, double), &parser);
          }
          i++;
          break;
        case 'e':
          parser.specifier = 'e';
          if (parser.length == 'L') {
            flag_eE((long double)va_arg(ptr, long double), &parser);
          } else {
            flag_eE((long double)va_arg(ptr, double), &parser);
          }
          i++;
          break;
        case 'E':
          parser.specifier = 'E';
          if (parser.length == 'L') {
            flag_eE((long double)va_arg(ptr, long double), &parser);
          } else {
            flag_eE((long double)va_arg(ptr, double), &parser);
          }
          i++;
          break;
        case 'x':
          parser.specifier = 'x';
          flag_xX(va_arg(ptr, long int), &parser);
          i++;
          break;
        case 'X':
          parser.specifier = 'X';
          flag_xX(va_arg(ptr, long int), &parser);
          i++;
          break;
        case 'o':
          parser.specifier = 'o';
          flag_o(va_arg(ptr, long int), &parser);
          i++;
          break;
        case 'p':
          parser.specifier = 'p';
          flag_p(va_arg(ptr, void *), &parser);
          i++;
          break;
        case 'n':
          parser.specifier = 'n';
          i++;
          int *numberT = (int *)va_arg(ptr, void *);
          *numberT = count;
          break;
      }

      for (int r = 0; parser.mass[r] != '\0'; r++, count++) {
        str[count] = parser.mass[r];
      }
      if (parser.mass[0] == '\0' && parser.specifier == 'c') {
        str[count] = '\0';
        count++;
      }
    } else {
      str[count] = format[i];
      i++;
      count++;
    }
  }

  str[count] = '\0';
  va_end(ptr);
  return count;
}
