CC=gcc
CFLAGS=-Wall

DEBUG=-g
LIB=-lSDL2

SRC=\
	flou.c

OBJ= $(SRC:.c=.o)

BIN=\
	flou.out

flou: $(OBJ)
	$(CC) -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp 
