#ifndef SOLVER_H
#define SOLVER_H
#include <SDL2/SDL.h>
#include <stdio.h>

// Variables globales
extern char filename[];
extern char grid[256][256];
extern int grid_len_x;
extern int grid_len_y;

int solver(char word[], int** Start, int** End);
void drawSolution(SDL_Surface *surface, int x1, int y1, int x2, int y2, int r, int g, int b);

#endif
