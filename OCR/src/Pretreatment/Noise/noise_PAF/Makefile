CC=gcc
CFLAGS=-Wall

LIB=-lSDL2 -lm

SRC=\
	 ../../Utils/convert.c \
	 ../../Utils/sdl_utils.c \
	 ../../GreyScale/greyscale.c \
	 ../../blur/blur.c \
	gaussNoise.c \
	medianFilter.c

OBJ=$(SRC:.c=.o)

BIN=noise.out \

noise: $(OBJ)
	$(CC) -g -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) -g $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp
