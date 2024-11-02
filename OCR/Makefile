CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0` -rdynamic -Wall -Wextra -Wvla -pedantic -std=c99 -fsanitize=address -g

LIB=`pkg-config --libs gtk+-3.0` -lSDL2 -lm -fsanitize=address -g

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
	src/Pretreatment/crop/crop.c \
	src/Pretreatment/rotation/rotate.c \
	./main.c \
	src/Gtk/interface.c

OBJ=$(SRC:.c=.o)

main: $(OBJ)
	$(CC) -o main.out $+ $(LIB) -export-dynamic

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ) main.out output/*.bmp output/letter/*.bmp output/letter/*/
