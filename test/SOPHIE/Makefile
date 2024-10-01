CC=gcc
CFLAGS=-Wall -Iinclude

LD=gcc
LDFLAGS=-g
LIB=-lSDL2 -lSDL2_image -lm

SRC_DIR=src


SRC= rotate.c
#rotate.c

OBJ= $(SRC:.c=.o)

BIN= rotate.out
#rotate.out

rotation: $(OBJ)
	$(LD) $(LDFLAGS) -o rotate.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ) $(BIN)

run: $(BIN)
	./$(BIN)


