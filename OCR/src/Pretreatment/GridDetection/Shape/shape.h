#ifndef SHAPE_H
#define SHAPE_H

#include <SDL2/SDL.h>

typedef struct Shape {
    int id;
    int Cx, Cy;
    int MaxX, MaxY;
    int MinX, MinY;
    int Len;
} Shape;

Shape* CreateShape(int id, int x, int y);
void FindShape(Shape* s, int** surface, int** Map, int x, int y, int height, int width);
int IsShapeValid(SDL_Surface* surface, Shape* s);
#endif

