# Makefile for C++ project
CC = g++
CFLAGS = -I include/ -std=c++20
SRC_DIR = ./src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,obj/%.o,$(SRC))
OUT_DIR = ./out
OUT = $(OUT_DIR)/program
INPUT_DIR = ./resources/input

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

run_sample2d: $(OUT)
	$(OUT) $(INPUT_DIR)/sample2d.csv 0.2 10 > $(OUT_DIR)/output_2d.csv

run_sample3d: $(OUT)
	$(OUT) $(INPUT_DIR)/sample3d.csv 1 10 > $(OUT_DIR)/output_3d.csv

clean:
	rm -f $(OBJ) $(OUT)