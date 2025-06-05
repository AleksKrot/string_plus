#include <stdarg.h>  // Предназначена для работы с функциями с переменным числом аргументов
#include <stdio.h>

int sprintf(char *str, const char *format, ...);

int main() {
  char buffer[256];
  int count = sprintf(buffer, "Hello, %c%d%%!", 'A', -100);
  printf("%s\nCount = %d", buffer, count);

  return 0;
}

int sprintf(char *str, const char *format, ...) {
  va_list args;  // тип для хранения информации о текущей позиции в списке
                 // аргументов
  va_start(args,
           format);  // ф-я инициализирует переменную args типа va_list для
                     // доступа к дополнительным аргументам функции format — имя
                     // последнего фиксированного параметра функции, после
                     // которого начинаются переменные аргументы.

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

    switch (*format++) {
      case 'c': {
        char c = (char)va_arg(args, int);  // char повышается до int в va_arg
                                           // (стандартные повышения аргументов)
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