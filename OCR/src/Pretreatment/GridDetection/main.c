#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "grid.h"
#include "../Utils/sdl_utils.h"

int main()
{
    for (int i = 1; i < 9; i++)
    {
        printf("Processing image %i...\n", i);
        char* s = NULL;
        asprintf(&s, "img/img%i.bmp", i);
        char *sg = NULL;
        asprintf(&sg, "img/imgGrid%i.bmp", i);
        sdl_setup();
        SDL_Surface* surface = SDL_LoadBMP(s);
        if (surface == NULL)
        {
            err(1, "Unable to load image: %s\n", SDL_GetError());
        }
        ProcessGrid(surface);
        SDL_SaveBMP(surface, sg);
        SDL_FreeSurface(surface);
        SDL_Quit();
        free(s);
        free(sg);
    }

    return 0;
}
