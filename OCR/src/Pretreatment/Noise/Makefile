CC=gcc
CFLAGS=-Wall

LD=gcc
LDFLAGS=-g
LIB=-lSDL2

SRC=\
	../Utils/sdl_utils.c \
	noise.c

OBJ= $(SRC:.c=.o)

BIN=\
	noise.out

noise: $(OBJ)
	$(LD) $(LDFLAGS) -o noise.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) $(BIN) *.bmp

