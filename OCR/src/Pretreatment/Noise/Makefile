CC=gcc
CFLAGS=-Wall -Wextra -fsanitize=address -g

LIB=-lSDL2 -lm -fsanitize=address

SRC=\
	 ../Utils/sdl_utils.c \
	 ../GreyScale/greyscale.c \
	 ../Contrast/contrast.c \
	gauss.c \
	median.c

OBJ=$(SRC:.c=.o)

BIN=noise.out \

noise: $(OBJ)
	$(CC) -g -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) -g $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp
