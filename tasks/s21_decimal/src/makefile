CC=gcc
CFLAGS=-Werror -Wextra -Wall -std=c11 -O2
LDFLAGS=-O2 #-g -fsanitize=address,undefined

GCOV_FLAGS=--coverage
LCHECK_FLAGS != pkg-config --libs check

DECIMAL_SRC != find main -type f -name \*.c
TEST_SRC != find tests -type f -name \*.c
SRC=$(DECIMAL_SRC) $(TEST_SRC)

BUILD_DIR=../build

OBJ_DIR=$(BUILD_DIR)/objects
OBJ_SUBDIRS=$(patsubst %, $(OBJ_DIR)/%, $(shell find . -type d))

GCOV_DIR=$(BUILD_DIR)/gcov
GCOV_OBJ_DIR=$(GCOV_DIR)/objects
GCOV_REPORT_DIR=$(GCOV_DIR)/report
GCOV_OBJ_SUBDIRS=$(patsubst %, $(GCOV_OBJ_DIR)/%, $(shell find . -type d))
GCOV_OBJ=$(patsubst %.c, $(GCOV_OBJ_DIR)/%.o, $(SRC))

DECIMAL_OBJ=$(DECIMAL_SRC:%.c=$(OBJ_DIR)/%.o)
TEST_OBJ=$(TEST_SRC:%.c=$(OBJ_DIR)/%.o)

OBJ=$(DECIMAL_SRC:.c=.o) $(TEST_SRC:.c=.o)

# Main

all: s21_decimal.a

clean:
	rm -rf test gcov_test $(BUILD_DIR) *.a *.out .clang-format

rebuild: clean all

# Decimal lib itself

s21_decimal.a: $(OBJ_SUBDIRS) $(DECIMAL_OBJ)
	ar rcs $@ $(DECIMAL_OBJ)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Tests

test: $(BUILD_DIR)/test

$(BUILD_DIR)/test: $(OBJ_SUBDIRS) $(TEST_OBJ) s21_decimal.a
	$(CC) $(LDFLAGS) $(TEST_OBJ) s21_decimal.a -o $@ $(LCHECK_FLAGS) -lm

# gcov_report

gcov_report: $(GCOV_REPORT_DIR)/index.html

$(GCOV_REPORT_DIR)/index.html: $(GCOV_DIR)/gcov_report.info
	genhtml -o $(GCOV_REPORT_DIR) $<

$(GCOV_DIR)/gcov_report.info: $(GCOV_DIR)/gcov_test
	./$<
	lcov -c -d $(GCOV_OBJ_DIR) -o $(GCOV_DIR)/gcov_report.info

$(GCOV_DIR)/gcov_test: $(GCOV_OBJ_SUBDIRS) $(GCOV_REPORT_DIR) $(GCOV_OBJ)
	$(CC) -g $(GCOV_FLAGS) $(GCOV_OBJ) -o $@ $(LCHECK_FLAGS) -lm

$(GCOV_OBJ_DIR)/main/%.o: main/%.c
	$(CC) -c -g $(GCOV_FLAGS) $< -o $@

$(GCOV_OBJ_DIR)/tests/%.o: tests/%.c
	$(CC) -c $(CFLAGS) $< -o $@

# build hierarchy generator

$(OBJ_SUBDIRS) $(GCOV_OBJ_SUBDIRS) $(GCOV_REPORT_DIR):
	mkdir -p $@
