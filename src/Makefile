CC = gcc 
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
TEST_FLAGS = -lcheck -lm -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage 
GCOVR_FLAGS = --txt-metric branch --html --html-details -o gcov_report.html

SRC_DIR = .
TEST_DIR = ./tests

.PHONY: all install test gcov_report clean rebuild

all: s21_string.a test gcov_report

install: #TODO поменять gcovr
		sudo apt-get update && sudo apt-get install check gcovr

s21_string.a:
		$(CC) $(CFLAGS) -c $(SRC_DIR)/s21_string.c -o $(SRC_DIR)/s21_string.o
		$(CC) $(CFLAGS) -c $(SRC_DIR)/s21_sprintf.c -o $(SRC_DIR)/s21_sprintf.o
		ar rcs $(SRC_DIR)/s21_string.a $(SRC_DIR)/s21_string.o $(SRC_DIR)/s21_sprintf.o

test: s21_string.a
		$(CC) $(CFLAGS) $(GCOV_FLAGS) -I$(SRC_DIR) $(TEST_DIR)/s21_string_test.c $(SRC_DIR)/s21_string.a -o $(TEST_DIR)/s21_string_test $(TEST_FLAGS)
		$(TEST_DIR)/s21_string_test

gcov_report: test
		gcovr $(GCOVR_FLAGS)

clean:
		rm -f $(SRC_DIR)/s21_string.a $(SRC_DIR)/*.o $(SRC_DIR)/*.html $(SRC_DIR)/*.css
		rm -f $(TEST_DIR)/s21_string_test $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno 

rebuild: clean all