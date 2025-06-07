#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>
#include <stdbool.h>

// Структура для хранения флагов формата
typedef struct {
  bool minus;  // Флаг выравнивания по левому краю
  bool plus;   // Флаг обязательного отображения знака +
  bool space;  // Флаг отображения пробела вместо знака +
} Flags;

// Структура для хранения информации о ширине
typedef struct {
  int number;  // Числовое значение ширины
} Width;

// Структура для хранения информации о точности
typedef struct {
  int number;  // Числовое значение точности
} Precision;

// Структура для хранения модификаторов длины
typedef struct {
  bool h;  // Модификатор short
  bool l;  // Модификатор long
} Length;

// Структура для хранения информации о спецификаторах
typedef struct {
  bool c;        // Символ
  bool d;        // Целое число со знаком
  bool f;        // Число с плавающей точкой
  bool s;        // Строка
  bool u;        // Целое число без знака
  bool percent;  // Символ процента
} Specifier;

// Основная структура для хранения всей информации о формате
typedef struct {
  Flags flags;          // Флаги формата
  Width width;          // Ширина поля
  Precision precision;  // Точность
  Length length;        // Модификаторы длины
  Specifier spec;       // Спецификаторы
} Format;

// Инициализация структуры Format значениями по умолчанию
static inline void init_format(Format *format) {
  format->flags.minus = false;
  format->flags.plus = false;
  format->flags.space = false;

  format->width.number = 0;
  format->precision.number = 0;

  format->length.h = false;
  format->length.l = false;

  format->spec.c = false;
  format->spec.d = false;
  format->spec.f = false;
  format->spec.s = false;
  format->spec.u = false;
  format->spec.percent = false;
}

// Основная функция форматированного вывода
int s21_sprintf(char *str, const char *format, ...);

// Функция парсинга строки формата
const char *parse_format(const char *fmt, Format *format);

// Функция обработки аргументов согласно формату
void process_format(Format *format, va_list args, char **buffer);

#endif  // S21_SPRINTF_H