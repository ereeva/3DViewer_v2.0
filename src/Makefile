PROJECT_NAME := SmartCalc2_0
BUILD_DIR := build
OS := $(shell uname -s)
CC=qmake

ifeq ($(OS), Linux)
	CC=qmake6
endif

all: build

.PHONY: build
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CC) ../$(PROJECT_NAME)/ && make
