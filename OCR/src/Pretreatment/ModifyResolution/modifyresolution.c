#include <SDL2/SDL.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Utils/convert.h"
#include "../Utils/sdl_utils.h"

SDL_Surface* modifyresolution(SDL_Surface* surface, int new_width, int new_height) 
{
    if (surface == NULL) {
        fprintf(stderr, "Surface is NULL, can't modify resolution\n");
        exit(EXIT_FAILURE);
    }

    if (SDL_LockSurface(surface) < 0) {
        fprintf(stderr, "SDL_LockSurface failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Surface* resized_surface = SDL_CreateRGBSurfaceWithFormat(0, new_width, new_height, 24, SDL_PIXELFORMAT_RGB24);

    if (resized_surface == NULL) {
        SDL_UnlockSurface(surface);
        fprintf(stderr, "Failed to create resized surface: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    int original_width = surface->w;
    int original_height = surface->h;
    int original_pitch = surface->pitch;
    int new_pitch = resized_surface->pitch;
    int bpp = surface->format->BytesPerPixel;

    Uint8* original_pixels = (Uint8*)surface->pixels;
    Uint8* new_pixels = (Uint8*)resized_surface->pixels;

    for (int j = 0; j < new_height; j++) {
        for (int i = 0; i < new_width; i++) {
            int orig_x = (i * original_width) / new_width;
            int orig_y = (j * original_height) / new_height;

            Uint8* original_pixel = original_pixels + orig_y * original_pitch + orig_x * bpp;
            Uint8* new_pixel = new_pixels + j * new_pitch + i * bpp;

            for (int k = 0; k < bpp; k++) {
                new_pixel[k] = original_pixel[k];
            }
        }
    }

    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);
    surface = resized_surface;
    return surface;
}
int main(int argc, char* argv[]) {
    convert(argv[1]);
    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP("img.bmp"); //convert() create a img.bmp

    SDL_Surface* a = modifyresolution(surface, 30, 30);

    SDL_SaveBMP(a, "img.bmp");
    SDL_FreeSurface(surface);
    SDL_FreeSurface(a);

    sdl_close();
}
