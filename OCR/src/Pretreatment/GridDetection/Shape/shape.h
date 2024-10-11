#ifndef SHAPE_H
#define SHAPE_H

#include <SDL2/SDL.h>

typedef struct Shape {
    int id;
    int Cx, Cy;
    int h,w;
    int Maxj, Maxi;
    int Minj, Mini;
    int Len;
} Shape;

Shape* CreateShape(int id, int x, int y);
void ComputeShape(Shape* s);
void FindShape(Shape* s, int** surface, int** Map, int x, int y, int height, int width);
int IsShapeValid(SDL_Surface* surface, Shape* s);
#endif

