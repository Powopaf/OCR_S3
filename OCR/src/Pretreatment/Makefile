# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address
LDFLAGS = -lSDL2
TARGET = greyscale.out

SRC = GreyScale/greyscale.c Utils/convert.c Utils/sdl_utils.c

all: $(TARGET)

# Compilation
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Nettoyage
clean:
	rm -f $(TARGET)

# Règle pour forcer la recompilation
.PHONY: all clean

