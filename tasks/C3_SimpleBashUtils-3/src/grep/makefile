CC=gcc
CFLAGS=-c -Werror -Wextra -Wall -std=c99
LDFLAGS=#-g -fsanitize=address,undefined

all: s21_grep

test_grep: test_grep.o ../common/test/test.o
	$(CC) $(LDFLAGS) $^ -o $@

s21_grep: grep.o ../common/command_line_parser/command_line_parser.o
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o s21_grep test_grep

rebuild: clean all
