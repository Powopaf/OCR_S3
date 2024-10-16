#ifndef MANIPULATION_H
#define MANIPULATION_H

#include "SDL2/SDL.h"

SDL_Surface *rotation(SDL_Surface *image, double angle);
SDL_Surface *Rotation_shearing(SDL_Surface *image, double angle);

uint32_t getPixel(SDL_Surface *surface, int x, int y);

void putPixel(SDL_Surface *surface, int x, int y, uint32_t pixel);
#endif
