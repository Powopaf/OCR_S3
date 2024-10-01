CC=gcc
CFLAGS=-Wall -Iinclude

LD=gcc
LDFLAGS=-g
LIB=-lSDL2 -lm


SRC= rotate.c \
	../Utils/convert.c \
	../Utils/sdl_utils.c

OBJ= $(SRC:.c=.o)

BIN= rotate.out

rotation: $(OBJ)
	$(LD) $(LDFLAGS) -o rotate.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp

