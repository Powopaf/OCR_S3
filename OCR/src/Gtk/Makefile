CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0` `sdl2-config --cflags` -rdynamic -Wall -Wextra -Wvla -pedantic -std=c99

LD=gcc
LDFLAGS=-g '-export-dynamic'
LIB=`pkg-config --libs gtk+-3.0` `sdl2-config --libs` -lSDL2_image

SRC=\
	interface.c

OBJ= $(SRC:.c=.o)

BIN=\
	interface.out

interface: $(OBJ)
	$(LD) $(LDFLAGS) -o $(BIN) $+ $(LIB)

interface_debug: $(OBJ)
	$(LD) $(LDFLAGS) $(LDFLAGS) -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN)

