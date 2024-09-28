CC=gcc
CFLAGS=-Wall

DEBUG=-g
LIB=-lSDL2

SRC=\
	blur.c \
	../Utils/sdl_utils.c \
	../Utils/convert.c

OBJ= $(SRC:.c=.o)

BIN=\
	blur.out

blur: $(OBJ)
	$(CC) -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp 
