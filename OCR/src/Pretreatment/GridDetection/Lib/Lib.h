#ifndef LIB_H
#define LIB_H

#include <SDL2/SDL.h>
#include "../Shape/shape.h"
#include "../List/Node.h"

SDL_Surface* DuplicateSurface(SDL_Surface* surface);
void MallocMatrix(int ***arr, int sizex, int sizey);
void FreeMatrix(int **arr, int sizex);

int IsOnSurface(int x, int y, int h, int w);
void InitMatrix(SDL_Surface *surface, int*** Map, int*** surf);
void PrintNodeList(Node* lst, char* name);
double distance(int x1, int y1, int x2, int y2);

int ListSum(Node* lst);
Node** ReduceArray(Node** lst, int* size, int nsize);
void FindShapePosMatrix(Node* shapeList, int* j, int* i);

void Draw(SDL_Surface *surface, Node* s, int r, int g, int b);
void DrawList(SDL_Surface* surface, Node** clusterList, int size);

#endif

