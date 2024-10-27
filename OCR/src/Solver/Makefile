# Compiler and Linker
CC := gcc

# Compiler Flags
CFLAGS := -Wall -Wextra -g -fsanitize=address

# Linker Flags and Libraries
LDFLAGS := -lm

# Source Files
SRC := \
   	solver.c

# Object Files (Automatically replace .c with .o)
OBJ := $(SRC:.c=.o)

# Output Binary
BIN := solver.out

# Default Target
all: $(BIN)

# Link the object files to create the final binary
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Target to remove all generated files
clean:
	rm -f $(OBJ) $(BIN)

# Phony Targets (These targets are not actual files)
.PHONY: all clean

