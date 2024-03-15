_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lm

.PHONY: clean check-syntax compile-all

OBJ_DIR := obj
BIN_DIR := bin
SRC_DIR := src

# compile rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< -I./include

$(OBJ_DIR)/%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Variable for object files
OBJECTS = $(OBJ_DIR)/map.o $(OBJ_DIR)/maze.o $(OBJ_DIR)/loader.o $(OBJ_DIR)/writer.o $(OBJ_DIR)/prim.o 

# Define targets for executables
main: $(OBJ_DIR)/main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $^ $(LDFLAGS) -I./include

app-generate-maze: $(OBJ_DIR)/app-generate-maze.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/app-generate-maze $^ $(LDFLAGS) -I./include

app-generate-random-maze: $(OBJ_DIR)/app-generate-random-maze.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/app-generate-random-maze $^ $(LDFLAGS) -I./include

# put all your applications and tests executables as prerequisite of this rule
compile-all: main app-generate-maze app-generate-random-maze

# rule to remove all .o files and all executables
clean:
	-rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*

# rule to valgrind main
valgrind_main: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(BIN_DIR)/main

# rule to valgrind app-generate-maze
valgrind_app-generate-maze: app-generate-maze
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(BIN_DIR)/app-generate-maze

# # Individual rules for compiling source files
# $(OBJ_DIR)/map.o: $(SRC_DIR)/map.c 
# 	$(CC) $(CFLAGS) -o $@ -c $<

# $(OBJ_DIR)/maze.o: $(SRC_DIR)/maze.c
# 	$(CC) $(CFLAGS) -o $@ -c $<

# $(OBJ_DIR)/loader.o: $(SRC_DIR)/loader.c
# 	$(CC) $(CFLAGS) -o $@ -c $<

# $(OBJ_DIR)/writer.o: $(SRC_DIR)/writer.c
# 	$(CC) $(CFLAGS) -o $@ -c $<

# $(OBJ_DIR)/prim.o: $(SRC_DIR)/prim.c
# 	$(CC) $(CFLAGS) -o $@ -c $<