CC = gcc 
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
TEST_FLAGS = -lcheck -lm -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage 
GCOVR_FLAGS = --txt-metric branch --html --html-details -o gcov_report.html

SRC_DIR = .

.PHONY: all install test gcov_report clean rebuild

all: s21_string.a test gcov_report

install: #TODO поменять gcovr
		sudo apt-get update && sudo apt-get install check
		sudo apt-get install gcovr

s21_string.a: #TODO переименовать s21_string_function
		$(CC) $(CFLAGS) -c $(SRC_DIR)/s21_string_function.c -o $(SRC_DIR)/s21_string_function.o
		ar rcs $(SRC_DIR)/s21_string.a $(SRC_DIR)/s21_string_function.o

test: s21_string.a
		$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC_DIR)/s21_string_test.c $(SRC_DIR)/s21_string.a -o $(SRC_DIR)/s21_string_test $(TEST_FLAGS)
		$(SRC_DIR)/s21_string_test

gcov_report: test
		gcovr $(GCOVR_FLAGS)

clean: #TODO почитать как называется это место
		rm -f $(SRC_DIR)/s21_string_function $(SRC_DIR)/s21_string_test $(SRC_DIR)/*.o $(SRC_DIR)/*.a $(SRC_DIR)/*.gcda $(SRC_DIR)/*.gcno $(SRC_DIR)/*.html $(SRC_DIR)/*.css

rebuild: clean all