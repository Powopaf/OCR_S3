#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include "Shape/shape.h"
#include "Lib/Lib.h"
#include "../Utils/sdl_utils.h"
#include "List/Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../crop/crop.h"
#include "../Utils/resize.h"
#include "../../NeuralNetwork/NeuralNetwork.h"
#include "Placement/placeInGrid.h"
#include "../../Solver/solver.h"

typedef struct Letter
{
    char letter;
    int x;
    int y;
} Letter;

void AverageClusterSize(Node** shapeList, int** visited, int id, double* avHeight, double* avWidth);
void AdjustList(Node** lst);
void ShapeFilter(Node** shapeList);
Node** CreateLine(Node** shapeList, int* size);
void FindLine(int** visited, Node** shapeList, Shape* shape,int id);
//void ClusterFilter(Node** clusterList, int* size,SDL_Surface* surface);
void ProcessGrid(SDL_Surface *surface);
Shape* FindNearestShape(Node** shapeList, Shape* s, int** visited, int MaxDist, double avH, int id);

#endif

