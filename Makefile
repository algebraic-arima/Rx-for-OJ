# Single-file C++ compiler Makefile
# Assumes your source is in . or src/ (e.g., main.cpp)

CXX := g++
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra -pipe
LDFLAGS :=

SRC := $(wildcard *.cpp) $(wildcard src/*.cpp)
BIN := bin/code

# Fail early if no source found
ifeq ($(strip $(SRC)),)
$(error No .cpp source file found in . or src/)
endif

.PHONY: build run clean

build:
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

run:
	./$(BIN)

clean:
	rm -rf bin
