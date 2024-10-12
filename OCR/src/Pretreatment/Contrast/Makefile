CC=gcc
CFLAGS=-Wall
DEBUG=-g
LIB=-lSDL2

SRC=\
	../Utils/convert.c \
	../Utils/sdl_utils.c \
	../GreyScale/greyscale.c \
	contrast.c

OBJ=$(SRC:.c=.o)

BIN=\
	contrast.out

contrast: $(OBJ)
	$(CC) $(DEBUG) -o contrast.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp
