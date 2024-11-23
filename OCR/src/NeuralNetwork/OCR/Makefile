# Compiler and Linker
CC := gcc

# Compiler Flags
CFLAGS := -Wall -Wextra -g -fsanitize=address

# Linker Flags and Libraries
LDFLAGS := -lSDL2 -lm

# Source Files
SRC_OCR := main.c \ NeuralNetwork.c \ NeuralNetworkTraining.c 
SRC_LIB := ../Lib/NeuralNetworkLib.c \ ../Lib/TrainingLib.c

# Object Files (Automatically replace .c with .o)
OBJ_OCR := $(SRC_OCR:.c=.o) $(SRC_LIB:.c=.o)

# Output Binaries
BIN_OCR := ocr.out

# Default Target
all: $(BIN_OCR)

# Link the object files to create the final binaries
$(BIN_OCR): $(OBJ_OCR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Target to remove all generated files
clean:
	rm -f $(OBJ_OCR) $(BIN_OCR)

# Phony Targets (These targets are not actual files)
.PHONY: all clean