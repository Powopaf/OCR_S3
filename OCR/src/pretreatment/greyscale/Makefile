CC=gcc
CFLAGS=-Wall

LD=gcc
LDFLAGS=-g
LIB=-lSDL2

SRC=\
	../Utils/convert.c \
	../Utils/sdl_utils.c \
	greyscale.c

OBJ= $(SRC:.c=.o)

BIN=\
	greyscale.out

greyscale: $(OBJ)
	$(LD) $(LDFLAGS) -o greyscale.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp

