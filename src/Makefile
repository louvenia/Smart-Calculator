CFLAGS := -std=c11 -pedantic
CPPFLAGS := -Wall -Werror -Wextra
CC = gcc
GFLAGS = --coverage
TFLAGS = -lcheck
OBJECTS = *.o
SOURCES := s21_SmartCalc/s21_smartcalc.c \
			s21_SmartCalc/s21_checking_expression.c \
			s21_SmartCalc/s21_operations_stack.c \
			s21_SmartCalc/s21_credit_calculator.c \
			s21_SmartCalc/s21_depozit_calculator.c \

SOURCES_TEST := test_calculator.c

all: clean tests

s21_smartcalc.a:
	@$(CC) $(CPPFLAGS) $(SOURCES) $(ASAN) -c
	@ar rcs s21_smartcalc.a $(OBJECTS)
	@rm *.o

tests: s21_smartcalc.a
	@$(CC) $(CPPFLAGS) $(ASAN) $(GFLAGS) s21_smartcalc.a $(SOURCES_TEST) $(TFLAGS) $(VAR) -o $@
	@./$@

check:
	clang-format -n $(SOURCES) $(SOURCES_TEST) s21_SmartCalc/*.h

leaks:
	CK_FORK=no leaks --atExit -- ./tests

gcov_report: all
	@$(CC) $(CPPFLAGS) $(SOURCES) $(GFLAGS) $(ASAN) -c
	@ar rcs s21_smartcalc.a $(OBJECTS)
	@rm *.o
	@$(CC) $(CPPFLAGS) $(ASAN) $(GFLAGS) s21_smartcalc.a $(SOURCES_TEST) $(TFLAGS) $(VAR) -o tests
	@./tests
	gcovr -r . --html --html-details -o report.html
	./tests
	open report.html

install:
	mkdir Build
	cmake s21_SmartCalc -B Build
	cmake --build Build

uninstall:
	cd Build && make clean
	rm -rf Build/CMakeCache.txt Build/s21_SmartCalc.app
	rm -r Build
dist:
	cd .. && tar -czf SRC_C7_SmartCalc_v1.0-0.tgz src

dist_clean:
	cd .. && rm SRC_C7_SmartCalc_v1.0-0.tgz

dvi: dvi_clean
	makeinfo user_guide.texi --html
	open ./user_guide/index.html

dvi_clean:
	rm -rf user_guide

clean:
	rm -rf $(OBJECTS) s21_smartcalc.a tests *.gcda *.gcno *.html *.css
