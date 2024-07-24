TESTS_DIR := ./tests
C_SRCS := $(wildcard *.c ./binary/*.c ./other_func/*.c ./decimal_helper/*.c)
C_OBJS := $(C_SRCS:%.c=%.o)

all: clean s21_decimal.a

s21_decimal.a: $(C_OBJS)
	ar rcs ./$@ $^

%.o: %.c
	gcc -c -std=c11 -g -Wall -Werror -Wextra $< -o $@

test: clean s21_decimal.a $(TESTS_DIR)/main.c
	gcc -std=c11 -Wall -Werror -Wextra $(TESTS_DIR)/*.c -o $(TESTS_DIR)/test.o -L. s21_decimal.a -lcheck -lsubunit -lm 
	$(TESTS_DIR)/test.o

clean:
	rm -rf *.o ./*/*.o *.a
	rm -rf *.gcno *.gcda *.info report.out *.gcov

gcov_report: clean s21_decimal.a
	gcc -fprofile-arcs -ftest-coverage -Wall -Werror -Wextra -std=c11 binary/*.c other_func/*.c decimal_helper/*.c *.c $(TESTS_DIR)/*.c -o tmp_gcov.o -L. s21_decimal.a -lcheck -lm -lsubunit
	./tmp_gcov.o
	gcov -f $(C_SRCS)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	make clean
