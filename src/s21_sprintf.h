#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>
#include <stdbool.h>

// Структура для хранения флагов
typedef struct {
  bool minus;  // Флаг выравнивания по левому краю
  bool plus;  // Флаг обязательного отображения знака +
  bool space;  // Флаг отображения пробела вместо знака +
  bool hashtag;
  bool zero;  // Флаг дополняет число слева нулями (0) вместо пробелов
} Flags;

// Структура для хранения ширины
typedef struct {
  int number;     // Числовое значение ширины
  bool asterisk;  // '*'
} Width;

// Структура для хранения точности
typedef struct {
  int number;     // Числовое значение точности
  bool asterisk;  // '*'
} Precision;

// Структура для хранения модификаторов длины
typedef struct {
  bool h;  // Модификатор short
  bool l;  // Модификатор long
  bool L;  // Модификатор long double
} Length;

// Структура для хранения спецификаторов
typedef struct {
  bool c;  // Символ
  bool d;  // Целое число со знаком
  bool i;  // Целое число со знаком
  bool e;  // Вывод числа в научном формате с маленькой буквой e
  bool E;  // Вывод числа в научном формате с заглавной буквой E
  bool f;  // Число с плавающей точкой
  bool g;  // Вывод чисел с плавающей точкой в компактном формате
  bool G;  // Вывод чисел с плавающей точкой в компактном формате
  bool o;  // Целое число в восьмеричном формате
  bool s;  // Строка
  bool u;  // Целое число без знака
  bool x;  // Целое число без знака в шестнадцатеричном формате с маленькими
           // буквами a–f
  bool X;  // Целое число без знака в шестнадцатеричном формате с заглавными
           // буквами A–F
  bool p;  // Вывод указателей
  bool n;  // Запись количества уже выведенных символов в переменную
  bool percent;  // Символ процента
} Specifier;

typedef struct {
  Flags flags;          // Флаги формата
  Width width;          // Ширина поля
  Precision precision;  // Точность
  Length length;        // Модификаторы длины
  Specifier spec;       // Спецификаторы
} Format;

// Функция парсинга строки формата
int s21_sprintf(char *str, const char *format, ...);
// Функция парсинга строки формата
const char *parse_format(const char *fmt, Format *format);
// Инициализация структуры Format значениями по умолчанию
void init_format(Format *format);
// Функция обработки аргументов согласно формату
const char process_format(Format *format, va_list args, char **buffert);

#endif