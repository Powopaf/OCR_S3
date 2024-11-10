#include "resize.h"

SDL_Surface* resize_surface(SDL_Surface* original_surface, int new_width, int new_height)
{

    SDL_Surface* resized_surface = SDL_CreateRGBSurfaceWithFormat(0, new_width, new_height, 24, SDL_PIXELFORMAT_RGB24);


    if (SDL_BlitScaled(original_surface, NULL, resized_surface, NULL) < 0) 
    {
        SDL_FreeSurface(resized_surface);
        return NULL;
    }
    SDL_FreeSurface(original_surface);
    return resized_surface;
}
