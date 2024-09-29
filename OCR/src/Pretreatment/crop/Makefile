CC=gcc
CFLAGS=-Wall
LIB=-lSDL2
SRC =\
	 crop.c \
	 ../Utils/convert.c \
	 ../Utils/sdl_utils.c

OBJ= $(SRC:.c=.o)

BIN=\
	crop.out

crop: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp
