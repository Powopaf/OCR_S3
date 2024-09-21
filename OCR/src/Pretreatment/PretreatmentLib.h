#ifndef PRETREATMENTLIB_H
#define PRETREATMENTLIB_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <err.h>



//convert
void convert(const char* path);

//sdl utils
void sdl_setup();
void sdl_close();

void drawline(SDL_Renderer *renderer,
        int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b);

#endif
