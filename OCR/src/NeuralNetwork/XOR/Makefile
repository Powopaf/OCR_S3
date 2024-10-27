# Compiler and Linker
CC := gcc

# Compiler Flags
CFLAGS := -Wall -Wextra -g -fsanitize=address

# Linker Flags and Libraries
LDFLAGS := -lm

# Source Files
SRC_XOR := XOR.c
SRC_TRAIN := XORTraining.c
SRC_LIB := ../NeuralNetworkLib.c

# Object Files (Automatically replace .c with .o)
OBJ_XOR := $(SRC_XOR:.c=.o) $(SRC_LIB:.c=.o)
OBJ_TRAIN := $(SRC_TRAIN:.c=.o) $(SRC_LIB:.c=.o)

# Output Binaries
BIN_XOR := xor.out
BIN_TRAIN := xor_train.out

# Default Target
all: $(BIN_XOR) $(BIN_TRAIN)

# Link the object files to create the final binaries
$(BIN_XOR): $(OBJ_XOR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_TRAIN): $(OBJ_TRAIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Target to remove all generated files
clean:
	rm -f $(OBJ_XOR) $(OBJ_TRAIN) $(BIN_XOR) $(BIN_TRAIN)

# Phony Targets (These targets are not actual files)
.PHONY: all clean

