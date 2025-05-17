CC=g++
CFLAGS=-std=c++17 -Werror -Wall -Wextra
LDFLAGS=
DEBUG_FLAGS=-g -fsanitize=address,undefined

GTEST_FLAGS:=$(shell pkg-config --libs gtest)
GCOV_FLAGS:=--coverage

BUILD_DIR=./build
SRC_DIR=./src
TEST_SRC_DIR=./tests
OBJ_DIR=$(BUILD_DIR)/obj
TEST_DIR=$(BUILD_DIR)/tests
TEST_OBJ_DIR=$(TEST_DIR)/obj
INC=./inc

SRC=$(shell find $(SRC_DIR) -type f -name \*.cpp)
OBJ=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
LIB=$(BUILD_DIR)/s21_matrix_oop.a
TEST_EXE=$(BUILD_DIR)/test
TEST_SRC=$(shell find $(TEST_SRC_DIR) -type f -name \*.cpp)
TEST_OBJ=$(patsubst $(TEST_SRC_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC))

GCOV_DIR=$(BUILD_DIR)/gcov
GCOV_OBJ_DIR=$(GCOV_DIR)/obj
GCOV_REPORT_DIR=$(GCOV_DIR)/report
GCOV_OBJ=$(patsubst $(SRC_DIR)/%.cpp, $(GCOV_OBJ_DIR)/%.o, $(SRC))
GCOV_TEST_EXE=$(BUILD_DIR)/gcov_test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) -c -I $(INC) $(CFLAGS) $< -o $@

s21_matrix_oop.a: $(LIB)

$(LIB): $(OBJ)
	mkdir -p $(@D)
	ar rcs $@ $^

all: $(LIB)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

test: $(TEST_EXE)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) -c -I $(INC) $(CFLAGS) $< -o $@

$(TEST_EXE): $(TEST_OBJ) $(LIB)
	mkdir -p $(@D)
	$(CC) $^ $(GTEST_FLAGS) -o $@

debug: $(BUILD_DIR)/debug

$(BUILD_DIR)/debug: $(SRC) $(TEST_SRC)
	$(CC) $^ $(DEBUG_FLAGS) $(GTEST_FLAGS) -o $@

$(GCOV_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) -c -I $(INC) $< $(GCOV_FLAGS) -o $@

$(GCOV_TEST_EXE): $(TEST_OBJ) $(GCOV_OBJ)
	$(CC) $^ $(GTEST_FLAGS) $(GCOV_FLAGS) -o $@

$(GCOV_DIR)/gcov_report.info: $(GCOV_TEST_EXE)
	./$<
	lcov -c -d $(GCOV_OBJ_DIR) -o $@

gcov_report: $(GCOV_DIR)/gcov_report.info
	mkdir -p $(GCOV_REPORT_DIR)
	genhtml -o $(GCOV_REPORT_DIR) $<