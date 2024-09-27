CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0` -rdynamic -Wall -Wextra -Wvla -pedantic -std=c99

LD=gcc
LDFLAGS=-g
LIB=`pkg-config --libs gtk+-3.0`

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

