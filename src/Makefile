CC=g++
CPPFLAGS=-Wall -Wextra -Werror -std=c++17
OFLAGS=-O2
LDFLAGS=-lgtest -pthread

PROJECT_NAME=3DViewer_v2_0
TEST_DIR=tests
BUILD_DIR=build
INSTALL_DIR=install
TEST=test
TEST_BUILD=$(TEST)_build
TEST_SRCS=$(wildcard $(PROJECT_NAME)/tests/*.cc $(PROJECT_NAME)/model/*.cc)
CLANG_FILES=$(shell find $(PROJECT_NAME) \( -name "*.cc" -o -name "*.h" \))

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	OPEN_CMD=./$(INSTALL_DIR)/$(PROJECT_NAME)
endif
ifeq ($(OS), Darwin)
	OPEN_CMD=open ./$(INSTALL_DIR)/$(PROJECT_NAME).app
endif

.PHONY: all $(TEST) $(TEST_BUILD) build install uninstall open gcov_report dvi dist clean clang style valgrind leaks

all: install

build:
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
	./$(TEST)

$(TEST_BUILD):
		$(CC) $(CPPFLAGS) $(OFLAGS) $(TEST_SRCS) -o $(TEST) $(LDFLAGS)

dist:
	mkdir -p viewer
	cp Makefile viewer
	cp -r $(PROJECT_NAME) viewer
	tar cvzf $(PROJECT_NAME).tgz viewer/
	rm -rf viewer

# dvi:


clean:
	rm -rf $(BUILD_DIR) $(TEST)

style:
	clang-format -n --style=Google $(CLANG_FILES)

clang:
	clang-format -i --style=Google $(CLANG_FILES)

valgrind: $(TEST_BUILD)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST)

leaks: $(TEST_BUILD)
	leaks -atExit -- ./$(TEST)
