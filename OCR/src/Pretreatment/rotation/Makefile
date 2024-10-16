CC=gcc
CFLAGS=-Wall -fsanitize=address èg

LD=gcc
LDFLAGS=-g
LIB=-lSDL2 -lm -fsanitize=address -g


SRC= rotate.c \
	../Utils/convert.c \
	../Utils/sdl_utils.c \
	main.c

OBJ= $(SRC:.c=.o)

BIN= rotate.out

rotation: $(OBJ)
	$(LD) $(LDFLAGS) -o rotate.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp

