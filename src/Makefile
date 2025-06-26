# Упрощенный и надежный Makefile

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic

# Имена целевых файлов
TARGET = s21_sprintf
TEST_TARGET = test_sprintf

# Исходные файлы
SRC = s21_sprintf.c s21_string.c
TEST_SRC = test_sprintf.c

# Объектные файлы
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Основная цель
all: $(TARGET)

# Сборка основной программы
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Сборка тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Правило для компиляции .c файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)

# Пересборка
rebuild: clean all

.PHONY: all test clean rebuild