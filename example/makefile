CFLAGS = -std=c99 -g -Wall -Wextra -Wformat

DEFIINES = -DMILO_CONFIG='"milo_config.h"'
SRC = $(wildcard ./main.c)
INCLUDE = -I./../ -I./include/

EXECUTABLE = main

build: $(SRC)
	gcc $(CFLAGS) -o $(EXECUTABLE) $(SRC) $(INCLUDE) $(DEFIINES)

run: build
	./$(EXECUTABLE)

debug: build
	gdb ./$(EXECUTABLE)