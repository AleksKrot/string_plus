#include <stdarg.h>  // Предназначена для работы с функциями с переменным числом аргументов
#include <stdio.h>

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

    switch (*format) {
      case 'c': {
        char c = (char)va_arg(args, int);  // char повышается до int в va_arg
                                           // (стандартные повышения аргументов)
        *str++ = c;
        count++;
        format++;
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
        format++;
        break;
      }
      default:
        // Неподдерживаемый спецификатор - просто копируем
        *str++ = '%';
        *str++ = *format++;
        count += 2;
        break;
    }
  }

  *str = '\0';  // Завершаем строку
  va_end(args);  // Освобождает ресурсы, связанные с va_list
  return count;  // Количество записанных символов (без учёта '\0')
}