# Компилятор и флаги
CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -D_POSIX_C_SOURCE=200809L

# Настройки
SRCS := $(shell find . -type f -name '*.c')
HDRS := $(shell find . -type f -name '*.h')
ALL_FILES = $(SRCS) $(HDRS)



S21_STRING_MODULE = s21_string.c
S21_STRING_H = s21_string.h


SOURCES_1 = $(S21_STRING_MODULE) $(S21_STRING_H) 



all: test

s21_string.o: $(SOURCES_1)
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

s21_string.a: s21_string.o
	ar rcs $@ $<

test:
	$(CC) $(CFLAGS) s21_string_test.c  -o test
clean:
	rm -f *.o *

rebuild: clean all

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr --std=c11 $(ALL_FILES)
cfn:
	clang-format -n $(ALL_FILES)
cfi:
	clang-format -i $(ALL_FILES)	

