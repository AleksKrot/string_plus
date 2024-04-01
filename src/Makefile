CFLAGS=-Wall -Wextra -Werror -std=c11
TESTFLAGS= -lcheck -lsubunit -lm
CFILES= s21_string.c

all: clean s21_string.a

test: s21_string.a
	gcc $(CFLAGS) ./test/*.c -o main -L. -l:s21_string.a $(TESTFLAGS)
	./main

gcov_report:
	gcc $(CFLAGS) -c ./test/*.c $(CFILES)
	gcc $(CFLAGS) ./test/*.c $(CFILES) -o main $(TESTFLAGS) -coverage
	./main
	# mkdir html_report
	# python3 -m gcovr -r . --html --html-details -o html_report/coverage_report.html --exclude test
	# open html_report/coverage_report.html
	lcov -t "report" -o report.info -c -d .
	genhtml -o report report.info
	rm -f main-* *.o

s21_string.a:
	gcc $(CFLAGS) -c ./*.c -lm
	ar rcs s21_string.a *.o
	ranlib s21_string.a

clang:
	cp ./../materials/linters/.clang-format ./
	clang-format -i *.c *.h test/*.c test/*.h
	rm -f .clang-format

control:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s ./main

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *c *h

rebuild: clean all

debug:
	gcc -g *.c -o s21_string -lm

clean:
	rm -f *.o *.a *.gcda *.gcno *.info main s21_string.a s21_string
	rm -rf html_report
	rm -rf report