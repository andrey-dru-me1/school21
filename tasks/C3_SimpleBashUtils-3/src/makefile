CC=gcc
CFLAGS=-c -Werror -Wextra -Wall -std=c11
LDFLAGS=-g -fsanitize=address,undefined

TEST_OBJ=common/test/test.o
VECTOR_OBJ=common/vector/vector.o
COMMAND_LINE_PARSER_OBJ=common/command_line_parser/command_line_parser.o
CAT_OBJ=cat/cat.o
GREP_OBJ=grep/grep.o

EXECUTABLES=common/command_line_parser/test_command_line_parser common/vector/test_vector cat/s21_cat grep/s21_grep cat/test_cat grep/test_grep
OBJECTS=$(COMMAND_LINE_PARSER_OBJ) $(TEST_OBJ) $(VECTOR_OBJ) $(CAT_OBJ) $(GREP_OBJ) $(EXECUTABLES:%=%.o)

test_vector: common/vector/test_vector.o $(TEST_OBJ)
	$(CC) $(LDFLAGS) $^ -o $(<:.o=)

test_command_line_parser: common/command_line_parser/test_command_line_parser.o $(TEST_OBJ) $(COMMAND_LINE_PARSER_OBJ)
	$(CC) $(LDFLAGS) $^ -o $(<:.o=)

test: test_vector test_command_line_parser

s21_cat: $(CAT_OBJ) $(COMMAND_LINE_PARSER_OBJ)
	$(CC) $(LDFLAGS) $^ -o cat/$@

test_cat: cat/test_cat.o $(TEST_OBJ)
	$(CC) $(LDFLAGS) $^ -o cat/$@

s21_grep: $(GREP_OBJ) $(COMMAND_LINE_PARSER_OBJ)
	$(CC) $(LDFLAGS) $^ -o grep/$@

test_grep: grep/test_grep.o $(TEST_OBJ)
	$(CC) $(LDFLAGS) $^ -o grep/$@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLES)
