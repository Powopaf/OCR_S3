CC=gcc
CFLAGS=-Wall

DEBUG=-g
LIB=-lSDL2 -lm

SRC=\
	src/Pretreatment/Utils/convert.c \
	src/Pretreatment/Utils/sdl_utils.c \
	src/Pretreatment/GreyScale/greyscale.c \
	src/Pretreatment/Binarisation/binarisation.c \
	src/Pretreatment/Contrast/contrast.c \
	src/Pretreatment/Noise/gauss.c \
	src/Pretreatment/blur/blur.c \
	src/Pretreatment/Noise/median.c \
	src/Pretreatment/GridDetection/grid.c \
	src/Pretreatment/GridDetection/Lib/Lib.c \
	src/Pretreatment/GridDetection/Shape/shape.c \
	src/Pretreatment/GridDetection/List/Node.c \
	./main.c

OBJ= $(SRC:.c=.o)

main: $(OBJ)
	$(CC) -o main.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) main.out output/*.bmp
