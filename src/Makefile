CC = gcc 
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_FLAGS = -lcheck -lm -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage 
GCOVR_FLAGS = --html --html-details -o gcov_report.html

SRC_DIR = .
TEST_DIR = ./tests

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%.o,$(TEST_SOURCES))
LIB_SOURCES = $(wildcard $(SRC_DIR)/*.c)
LIB_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.o,$(LIB_SOURCES))
LIB_HEADERS = $(wildcard $(SRC_DIR)/*.h)

.PHONY: all install test gcov_report clean rebuild

all: s21_string.a test gcov_report

install: #TODO поменять gcovr
		sudo apt-get update && sudo apt-get install check gcovr

s21_string.a: $(LIB_OBJECTS)
		ar rcs $(SRC_DIR)/s21_string.a $(LIB_OBJECTS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c $(TEST_DIR)/s21_string_test.h
		$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

test: $(TEST_OBJECTS) s21_string.a
		$(CC) $(CFLAGS) -I$(SRC_DIR) $(TEST_OBJECTS) $(SRC_DIR)/s21_string.a -o $(TEST_DIR)/s21_string_test $(TEST_FLAGS)
		$(TEST_DIR)/s21_string_test

gcov_report: clean
		$(CC) $(CFLAGS) $(GCOV_FLAGS) -I$(SRC_DIR) $(TEST_SOURCES) $(LIB_SOURCES) -o $(TEST_DIR)/s21_string_test $(TEST_FLAGS)
		$(TEST_DIR)/s21_string_test
		gcovr $(GCOVR_FLAGS)

clean:
		rm -f $(SRC_DIR)/s21_string.a $(SRC_DIR)/*.o $(SRC_DIR)/*.html $(SRC_DIR)/*.css
		rm -f $(TEST_DIR)/s21_string_test $(TEST_DIR)/*.o $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno

rebuild: clean all