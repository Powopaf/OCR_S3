CC=gcc
CFLAGS=-Wall

DEBUG=-g
LIB=-lSDL2

SRC=\
	blur.c \
	../Utils/sdl_utils.c \
	../Utils/convert.c \
	../GreyScale/greyscale.c

OBJ= $(SRC:.c=.o)

BIN=\
	blur.out

blur: $(OBJ)
	$(CC) -g -o $(BIN) $+ $(LIB)

debug_blur: $(OBJ)
	$(CC) $(DEBUG) -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) -g $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp 
