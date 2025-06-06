#include <stdarg.h>  // Предназначена для работы с функциями с переменным числом аргументов
#include <stdio.h>

#include "s21_string_function.h"

int sprintf(char *str, const char *format, ...);

int main() {
  char buffer[256];
  int count = sprintf(buffer, "Hi, %c=%d%%!", 'A', -100);
  printf("%s\nCount = %d", buffer, count);

  return 0;
}

int sprintf(char *str, const char *format, ...) {
  va_list args;  // Создаём объект для работы с аргументами, va_list -
                 // специальный тип для хранения информации об аргументах.
  va_start(args,
           format);  // Mакрос инициализирует переменную args, т.е. привязывает
                     // args к первому аргументу после format

  int count = 0;  // Счётчик записанных символов (возвращаемое значение)

  while (*format != '\0') {
    if (*format != '%') {
      // Обычный символ - копируем в выходную строку
      *str++ = *format++;
      count++;
      continue;
    }

    // Обработка спецификаторов
    format++;  // Пропускаем '%'

    if (*format == '%') {
      *str++ = *format++;
      count++;
      continue;
    }

    switch (*format++) {
      case 'c': {
        char c = (char)va_arg(args, int);  // char повышается до int
        *str++ = c;
        count++;
        break;
      }
      case 'd': {
        int num = va_arg(args, int);
        int is_negative = 0;

        // Обрабатываем отрицательные числа
        if (num < 0) {
          is_negative = 1;
          num = -num;  // Делаем число положительным для обработки
        }

        // Временный буфер для хранения цифр (максимум 10 цифр для 32-битного
        // int)
        char temp_buffer[12];  // С запасом для знака и нуль-терминатора
        int i = 0;

        // Обрабатываем 0 отдельно
        if (num == 0) {
          temp_buffer[i++] = '0';
        } else {
          // Разбираем число на цифры (в обратном порядке)
          while (num > 0) {
            temp_buffer[i++] = '0' + (num % 10);
            num /= 10;
          }
        }

        // Добавляем минус, если число было отрицательным
        if (is_negative) {
          temp_buffer[i++] = '-';
        }

        // Разворачиваем цифры в правильном порядке
        while (i > 0) {
          *str++ = temp_buffer[--i];  // Записываем цифры в str
          count++;
        }
        break;
      }
      case 'f': {
        double num = va_arg(args, double);
        int precision = 6;  // Стандартная точность для %f

        if (num < 0) {
          *str++ = '-';
          count++;
          num = -num;
        }

        int int_part = (int)num;  // Извлечение целой части
        double frac_part = num - int_part;  // Дробная часть

        // Преобразование целой части
        char int_buffer[20];
        int i = 0;

        if (int_part == 0) {
          int_buffer[i++] = '0';
        } else {
          while (int_part > 0) {
            int_buffer[i++] = '0' + (int_part % 10);
            int_part /= 10;
          }
        }

        // Запись целой части в обратном порядке
        while (i > 0) {
          *str++ = int_buffer[--i];
          count++;
        }

        // Добавление точки
        *str++ = '.';
        count++;

        // Преобразование дробной части
        for (int j = 0; j < precision; j++) {
          frac_part *= 10;
          int didgit = (int)frac_part;
          *str++ = '0' + didgit;
          count++;
          frac_part -= didgit;
        }

        break;
      }
      case 's': {
        const char *s = va_arg(args, const char *);
        if (s == NULL) {
          s = "(null)";  // Обработка NULL по аналогии со стандартным sprintf
        }
        int length = s21_strlen(s);
        s21_memcpy(str, s, length);
        str += length;
        count += length;
        break;
      }
      case 'u': {
        unsigned int num = va_arg(args, unsigned int);
        char temp_buffer[12];  // С запасом для знака и нуль-терминатора
        int i = 0;

        // Обрабатываем 0 отдельно
        if (num == 0) {
          temp_buffer[i++] = '0';
        } else {
          // Разбираем число на цифры (в обратном порядке)
          while (num > 0) {
            temp_buffer[i++] = '0' + (num % 10);
            num /= 10;
          }
        }
        // Разворачиваем цифры в правильном порядке
        while (i > 0) {
          *str++ = temp_buffer[--i];  // Записываем цифры в str
          count++;
        }
        break;
      }
      default:
        // Неподдерживаемый спецификатор - просто копируем
        *str++ = '%';
        *str++ = *(format - 1);
        count += 2;
        break;
    }
  }

  *str = '\0';  // Завершаем строку
  va_end(args);  // Освобождает ресурсы, связанные с va_list
  return count;  // Количество записанных символов (без учёта '\0')
}