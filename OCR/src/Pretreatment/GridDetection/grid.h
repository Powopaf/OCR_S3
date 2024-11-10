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

void AverageClusterSize(Node** cluster,double* avHeight, double* avWidth);
void AdjustList(Node** lst);
void ShapeFilter(Node** shapeList);
Node** CreateCluster(Node** shapeList, int* size);
void FindCluster(Node** visited, Node** cluster, Node** shapeList, Shape* shape);
Node** ClusterFilter(Node** clusterList, int* size);
void ProcessGrid(SDL_Surface *surface);

#endif

