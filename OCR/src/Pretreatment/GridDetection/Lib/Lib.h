#ifndef LIB_H
#define LIB_H

#include <SDL2/SDL.h>
#include "../Shape/shape.h"
#include "../List/Node.h"

void MallocMatrix(int ***arr, int sizex, int sizey);
void FreeMatrix(int **arr, int sizex);

int IsOnSurface(int x, int y, int h, int w);
void InitMatrix(SDL_Surface *surface, int*** Map, int*** surf);
void PrintNodeList(Node* lst, char* name);
double distance(Shape* s1, Shape* s2);

void Draw(SDL_Surface *surface, Node* s, int r, int g, int b);

#endif

