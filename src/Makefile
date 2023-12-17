CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -fmax-errors=1
OFLAGS=-O2
LDFLAGS=-lgtest -pthread
# GCOVFLAGS=--coverage
# GCOV_DIR=gcov

PROJECT_NAME=3DViewer_v2_0
SRC_DIR=3DViewer_v2_0
BUILD_DIR=build
INSTALL_DIR=install
OBJ_DIR=obj
OBJ_DIR_GCOV=$(OBJ_DIR)/$(GCOV_DIR)
OBJ_DIR_TEST=$(OBJ_DIR)/$(SRC_DIR)/tests

TEST_SRCS=$(wildcard $(SRC_DIR)/tests/*.cc $(SRC_DIR)/model/*.cc)
TEST_OBJS=$(patsubst %.cc, $(OBJ_DIR_TEST)/%.o, $(notdir $(TEST_SRCS)))
GCOV_OBJS=$(patsubst %.cc, $(OBJ_DIR_GCOV)/%.o, $(notdir $(TEST_SRCS)))
CLANG_FILES=$(shell find $(SRC_DIR) \( -name "*.cc" -o -name "*.h" \))

TEST=test
TEST_GCOV=$(TEST)_gcov
TEST_BUILD=$(TEST)_build
TEST_BUILD_GCOV=$(TEST_BUILD)_gcov

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	OPEN_CMD=./$(INSTALL_DIR)/$(PROJECT_NAME)
endif
ifeq ($(OS), Darwin)
	OPEN_CMD=open ./$(INSTALL_DIR)/$(PROJECT_NAME).app
endif

.PHONY: all $(TEST) $(TEST_BUILD) build install uninstall open gcov_report dvi dist clean clang style valgrind leaks

all: install

build: uninstall
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake ../$(PROJECT_NAME)/ && make

install: build
	mkdir -p $(INSTALL_DIR)
	cp -r $(BUILD_DIR)/$(PROGRAM) $(INSTALL_DIR)/

uninstall: clean
	rm -rf $(INSTALL_DIR)

open:
	$(OPEN_CMD)

$(TEST): $(TEST_BUILD)
	./$@ || true

$(TEST_BUILD): $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(OFLAGS) -o $(TEST)

$(OBJ_DIR_TEST)/%.o: %.cc
	mkdir -p $(OBJ_DIR_TEST)
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@

dist:
	mkdir -p viewer
	cp Makefile viewer
	cp -r $(PROJECT_NAME) viewer
	tar cvzf $(PROJECT_NAME).tgz viewer/
	rm -rf viewer

# dvi:


clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR) $(TEST)

style:
	clang-format -n --style=Google $(CLANG_FILES)

clang:
	clang-format -i --style=Google $(CLANG_FILES)

valgrind: $(TEST_BUILD)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST)

leaks: $(TEST_BUILD)
	leaks -atExit -- ./$(TEST)

# $(TEST_GCOV): $(TEST_BUILD_GCOV)
# 	$(MAKE) clean_gcda
# 	./$@ || true

# $(TEST_BUILD_GCOV): $(GCOV_OBJS)
# 	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(GCOVFLAGS) -o $(TEST_GCOV)

# $(OBJ_DIR_GCOV)/%.o: %.cc
# 	@mkdir -p $(OBJ_DIR_GCOV)
# 	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

# gcov_report: $(TEST_GCOV)
# 	mkdir -p $(GCOV_DIR)
# 	gcovr --html-details -o $(GCOV_DIR)/index.html --filter $(MODEL_DIR)/s21_\.\*
# 	open $(GCOV_DIR)/index.html

# lcov_report: $(TEST_GCOV)
# 	mkdir -p $(GCOV_DIR)
# 	lcov --capture --directory $(SRC_DIR) --exclude "$(CURDIR)/tests/*" --output-file $(GCOV_DIR)/coverage.info --no-external
# 	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/coverage.info 
# 	open $(GCOV_DIR)/index.html