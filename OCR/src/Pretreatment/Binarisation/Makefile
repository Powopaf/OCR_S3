CC=gcc
CFLAGS=-Wall
LDFLAGS=-g
LIB=-lSDL2 -lm

SRC=\
	../Utils/sdl_utils.c \
	binarisation.c

OBJ= $(SRC:.c=.o)

BIN=\
	bin.out

bin: $(OBJ)
	$(CC) -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp
