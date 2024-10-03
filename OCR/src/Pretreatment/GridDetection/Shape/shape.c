#include "../Shape/shape.h"
#include "../Lib/Lib.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

Shape* CreateShape(int id, int x, int y) {
    Shape* s = (Shape*)malloc(sizeof(Shape));
    if (s == NULL) {
        err(1, "ERROR Memory Allocation");
    }
    s->id = id;
    s->Cx = x;
    s->Cy = y;
    s->MaxX = x;
    s->MaxY = y;
    s->MinX = x;
    s->MinY = y;
    s->Len = 0;
    return s;
}

void FindShape(Shape* s, int** surface, int** Map, int x, int y, int height, int width) {
    Map[x][y] = s->id;
    s->Len++;

    // Update bounding box
    if (s->MaxX < x) s->MaxX = x;
    if (s->MinX > x) s->MinX = x;
    if (s->MaxY < y) s->MaxY = y;
    if (s->MinY > y) s->MinY = y;

    // Recursive exploration
    if (IsOnSurface(x+1, y, height, width) && Map[x+1][y] == 0 && surface[x+1][y] == 255)
        FindShape(s, surface, Map, x+1, y, height, width);
    
    if (IsOnSurface(x-1, y, height, width) && Map[x-1][y] == 0 && surface[x-1][y] == 255)
        FindShape(s, surface, Map, x-1, y, height, width);

    if (IsOnSurface(x, y+1, height, width) && Map[x][y+1] == 0 && surface[x][y+1] == 255)
        FindShape(s, surface, Map, x, y+1, height, width);
    
    if (IsOnSurface(x, y-1, height, width) && Map[x][y-1] == 0 && surface[x][y-1] == 255)
        FindShape(s, surface, Map, x, y-1, height, width);
}

int IsShapeValid(SDL_Surface* surface, Shape* s) {
    int lx = s->MaxX - s->MinX;
    int ly = s->MaxY - s->MinY;
    return (lx < surface->w / 8 && ly < surface->h / 8);
}

