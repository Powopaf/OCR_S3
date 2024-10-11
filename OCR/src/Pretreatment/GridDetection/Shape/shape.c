#include "../Shape/shape.h"
#include "../Lib/Lib.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

Shape* CreateShape(int id, int j, int i) {
    Shape* s = (Shape*)malloc(sizeof(Shape));
    if (s == NULL) {
        err(1, "ERROR Memory Allocation");
    }
    s->id = id;

    s->Cx = j;
    s->Cy = i;

    s->h = 0;
    s->w = 0;

    s->Maxj = j;
    s->Maxi = i;
    s->Minj = j;
    s->Mini = i;

    s->Len = 0;;
    return s;
}

void ComputeShape(Shape* s)
{
    s->h = s->Maxj - s->Minj;
    s->w = s->Maxi - s->Mini;
    s->Cx = s->Minj + (s->h)/2;
    s->Cy = s->Mini + (s->w)/2;

}

void FindShape(Shape* s, int** surface, int** Map, int j, int i, int height, int width) {
    Map[j][i] = s->id;
    s->Len++;

    // Update bounding box
    if (s->Maxj < j) s->Maxj = j;
    if (s->Minj > j) s->Minj = j;
    if (s->Maxi < i) s->Maxi = i;
    if (s->Mini > i) s->Mini = i;

    // Recursive exploration
    if (IsOnSurface(j+1, i, height, width) && Map[j+1][i] == 0 && surface[j+1][i] == 255)
        FindShape(s, surface, Map, j+1, i, height, width);
    
    if (IsOnSurface(j-1, i, height, width) && Map[j-1][i] == 0 && surface[j-1][i] == 255)
        FindShape(s, surface, Map, j-1, i, height, width);

    if (IsOnSurface(j, i+1, height, width) && Map[j][i+1] == 0 && surface[j][i+1] == 255)
        FindShape(s, surface, Map, j, i+1, height, width);
    
    if (IsOnSurface(j, i-1, height, width) && Map[j][i-1] == 0 && surface[j][i-1] == 255)
        FindShape(s, surface, Map, j, i-1, height, width);
}

int IsShapeValid(SDL_Surface* surface, Shape* s) {
    return (s->w < surface->w / 8 && s->h < surface->h / 8);
}

