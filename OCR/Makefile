CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0` -rdynamic -Wall -Wextra -g

LIB=`pkg-config --libs gtk+-3.0` -lSDL2 -lm -fsanitize=address -g

SRC=\
	src/Pretreatment/Utils/convert.c \
	src/Pretreatment/Utils/is_ubuntu.c \
	src/Pretreatment/Utils/sdl_utils.c \
	src/Pretreatment/Utils/resize.c \
	src/Pretreatment/GreyScale/greyscale.c \
	src/Pretreatment/Binarisation/binarisation.c \
	src/Pretreatment/GridDetection/grid.c \
	src/Pretreatment/GridDetection/Lib/Lib.c \
	src/Pretreatment/GridDetection/Shape/shape.c \
	src/Pretreatment/GridDetection/List/Node.c \
	src/Pretreatment/crop/crop.c \
	src/Pretreatment/rotation/rotate.c \
	src/NeuralNetwork/OCR/NeuralNetwork.c \
	src/NeuralNetwork/OCR/NeuralNetworkTraining.c \
	src/NeuralNetwork/Lib/NeuralNetworkLib.c \
	src/NeuralNetwork/Lib/TrainingLib.c \
	src/Pretreatment/GridDetection/Placement/placeInGrid.c \
	src/Solver/solver.c \
	src/Solver/drawSolution.c \
	./main.c \
	src/Gtk/interface.c

OBJ=$(SRC:.c=.o)

main: $(OBJ)
	$(CC) -o main.out $+ $(LIB) -export-dynamic

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ) main.out output/*.bmp
	./rmCluster.sh
