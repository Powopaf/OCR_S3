#ifndef ROTATE_H
#define ROTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

Uint8 getPixel(SDL_Surface *surface,int x, int y);
void setPixel(SDL_Surface *surface, int x, int y, Uint8 pixel);
SDL_Surface *rotation(SDL_Surface *image, double angle);
#endif
