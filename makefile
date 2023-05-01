SRC_DIR = ./src
# SRC_DIR es una variable que tiene el directorio del codigo fuente
# ./src es el directorio del codigo fuente
INC_DIR = ./inc
OUT_DIR = ./build
#  No entiendo bien para que hace esto
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

.DEFAULT_GOAL := all

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(OBJ_DIR): $(OUT_DIR)
	mkdir $(OBJ_DIR)

$(BIN_DIR): $(OUT_DIR)
	mkdir $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	gcc -c $< -o $@ -I $(INC_DIR)

all: $(OBJ_FILES) $(BIN_DIR)
	gcc -o $(BIN_DIR)/app.elf $(OBJ_FILES)
	echo $(SRC_FILES)
	echo $(OBJ_FILES)

clean: $(OUT_DIR)
	rm -r $(OUT_DIR)

doc:
	doxygen Doxyfile