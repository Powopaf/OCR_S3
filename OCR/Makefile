CC=gcc
CFLAGS=-Wall -Wextra

DEBUG=-g
LIB=-lSDL2 -lm

SRC=\
	src/Pretreament/Utils/convert.c \
	src/Pretreament/Utils/sdl_utils.c \
	src/Pretreament/GreyScale/greyscale.c \
	src/Pretreament/Binarisation/binarisation.c \
	src/Pretreament/Contrast/contrast.c \
	src/Pretreament/Noise/gauss.c \
	src/Pretreament/blur/blur.c \
	src/Preatrement/Noise/median.c \
	main.c

OBJ= $(SRC:.o=.c)

ocr: $(BIN)
	$(CC) -o ocr.out $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) ocr.out *.bmp
