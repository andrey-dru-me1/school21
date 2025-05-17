CC=gcc
CFLAGS=-Werror -Wall -Wextra
LDFLAGS=
DEBUG_FLAGS=-g -fsanitize=address,undefined

CHECK_FLAGS:=$(shell pkg-config --libs check)
NCURSES_FLAGS:=-lncursesw
GCOV_FLAGS:=--coverage

BUILD_DIR=./build
SRC_DIR=./src
TEST_SRC_DIR=./tests
OBJ_DIR=$(BUILD_DIR)/obj
TEST_DIR=$(BUILD_DIR)/tests
TEST_OBJ_DIR=$(TEST_DIR)/obj
INC=./inc

SRC=$(shell find $(SRC_DIR) -type f -name \*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
EXE=$(BUILD_DIR)/maze
BIN=bin/maze
TEST_EXE=$(BUILD_DIR)/test
TEST_SRC=$(shell find $(TEST_SRC_DIR) -type f -name \*.c)
TEST_OBJ=$(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC))
OBJ_FOR_TEST=$(filter-out %main.o, $(OBJ))

GCOV_DIR=$(BUILD_DIR)/gcov
GCOV_OBJ_DIR=$(GCOV_DIR)/obj
GCOV_REPORT_DIR=$(GCOV_DIR)/report
GCOV_OBJ=$(filter-out %main.o, $(patsubst $(SRC_DIR)/%.c, $(GCOV_OBJ_DIR)/%.o, $(SRC)))
GCOV_TEST_EXE=$(BUILD_DIR)/gcov_test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -c -I $(INC) $(CFLAGS) $< -o $@

$(EXE): $(OBJ)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) -I $(INC) $^ $(NCURSES_FLAGS) -o $@
	# ar rcs $@ $^

all: $(EXE)

install: $(BIN)

uninstall:
	rm $(BIN)

clean:
	rm -rf $(BUILD_DIR)

tests: test

rebuild: clean all

test: $(TEST_EXE)

debug: $(BUILD_DIR)/debug

$(BIN): $(EXE)
	mkdir -p $(@D)
	cp $< $@

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -c -I $(INC) $(CFLAGS) $< -o $@

$(TEST_EXE): $(TEST_OBJ) $(OBJ_FOR_TEST)
	mkdir -p $(@D)
	$(CC) $^ $(CHECK_FLAGS) $(NCURSES_FLAGS) -o $@

$(BUILD_DIR)/debug: $(SRC) $(TEST_SRC)
	$(CC) $^ $(DEBUG_FLAGS) $(CHECK_FLAGS) $(NCURSES_FLAGS) -I $(INC) -o $@

$(GCOV_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -c -I $(INC) $< $(GCOV_FLAGS) -o $@

$(GCOV_TEST_EXE): $(TEST_OBJ) $(GCOV_OBJ)
	$(CC) $^ $(CHECK_FLAGS) $(GCOV_FLAGS) $(NCURSES_FLAGS) -o $@

$(GCOV_DIR)/gcov_report.info: $(GCOV_TEST_EXE)
	./$<
	lcov -c -d $(GCOV_OBJ_DIR) -o $@

gcov_report: $(GCOV_DIR)/gcov_report.info
	mkdir -p $(GCOV_REPORT_DIR)
	genhtml -o $(GCOV_REPORT_DIR) $<