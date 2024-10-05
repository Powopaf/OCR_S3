CC=gcc
CFLAGS=-Wall

LDFLAGS=-g
LIB=-lSDL2 -lm

SRC=\
	 ../../Utils/convert.c \
	 ../../Utils/sdl_utils.c \
	 ../../GreyScale/greyscale.c \
	 ../../blur/blur.c \
	noise.c

OBJ=$(SRC:.c=.o)

BIN=noise.out

noise: $(OBJ)
	$(CC) -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp
