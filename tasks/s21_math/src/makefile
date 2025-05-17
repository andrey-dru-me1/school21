CC=gcc
CFLAGS=-Werror -Wextra -Wall -std=c11 -O3
LDFLAGS=-lm -O3 #-g -fsanitize=address,undefined

GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LCHECK_FLAGS=`pkg-config --libs check`

MATH_SRC=s21_asin_acos_atan.c s21_sin_cos_tan.c s21_ceil.c s21_floor.c s21_fmod.c s21_abs.c s21_fabs.c s21_sqrt.c s21_exp.c s21_log.c s21_pow.c

all: s21_math.a

s21_math.a: $(MATH_SRC:.c=.o)
	ar rcs $@ $^

test: test.o s21_math.a
	$(CC) $^ -o $@ $(LCHECK_FLAGS) $(LDFLAGS)

gcov_report: $(MATH_SRC) test.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $^ -o gcov_test $(LCHECK_FLAGS) $(LDFLAGS)
	./gcov_test
	lcov -c -d . -o gcov_report.info
	genhtml -o gcov_report gcov_report.info

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.[ch]
	rm -rf .clang-format

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.a test *gcov* *.gcno  *.gcda *.html *.css .clang-format

rebuild: clean all