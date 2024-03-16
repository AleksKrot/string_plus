COMP_FLAGS = -Wall -Werror -Wextra -std=c11

ifeq ($(shell uname), Linux)
	COMPILING_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
	COMPILING_FLAGS = -lcheck -lm
endif

all: test

s21_string.a:
	gcc $(COMP_FLAGS) -c sprintf_func.c sprintf_parser.c s21_string.c scanf_func.c
	ar rcs s21_string.a sprintf_func.o sprintf_parser.o s21_string.o scanf_func.o
	ranlib s21_string.a

test: s21_string.a
	gcc $(COMP_FLAGS) ./tests/*.c $(COMPILING_FLAGS) -o all_test s21_string.a
	./all_test > test_report.txt || true

gcov_report:
	gcc -c  $(COMP_FLAGS) --coverage *.c
	gcc -c  $(COMP_FLAGS) ./tests/*.c 
	gcc $(COMP_FLAGS) *.o -o s21_string $(COMPILING_FLAGS) -lgcov
	./s21_string > test_report.txt || true
	lcov -o string_tests.info -c -d .
	genhtml -o report string_tests.info
	open ./report/index.html


clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf *.gcno *.gcda *.gcov *.info
	rm -rf string_tests s21_string
	rm -rf all_test
	rm -rf report test_report.txt