#ifndef ROTATE_H
#define ROTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include "../Utils/sdl_utils.h"

SDL_Surface *rotation1(SDL_Surface *image, double angle);
void rotation(char* filename,double angle);
#endif
