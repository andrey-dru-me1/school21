CC=gcc
CFLAGS=-Werror -Wextra -Wall -std=c11
LDFLAGS=#-g -fsanitize=address,undefined

GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LCHECK_FLAGS=`pkg-config --libs check`

STRING_SRC=s21_strrchr.c s21_strncat.c s21_strerror.c s21_strtok.c s21_strlen.c s21_strcspn.c s21_strncmp.c s21_memcmp.c s21_trim.c s21_strchr.c s21_strstr.c s21_strpbrk.c s21_memchr.c s21_sprintf.c s21_to_upper.c s21_to_lower.c s21_memcpy.c s21_memset.c s21_strncpy.c s21_insert.c

all: s21_string.a

s21_string.a: $(STRING_SRC:.c=.o)
	ar rcs $@ $^

test: test.o s21_string.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LCHECK_FLAGS)

gcov_report: $(STRING_SRC) test.o
	$(CC) $(LDFLAGS) $(CFLAGS) $(GCOV_FLAGS) $^ -o gcov_test $(LCHECK_FLAGS)
	./gcov_test
	lcov -c -d . -o gcov_report.info
	genhtml -o gcov_report gcov_report.info

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.a test *gcov* *.gcno  *.gcda *.html *.css .clang-format

rebuild: clean all
