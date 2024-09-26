#include <SDL2/SDL.h>
#include <err.h>

//comment this include to run project uncomment to run blur.c
#include "../Utils/convert.h"
//////////////////////////////////////////////////////////////


void blurring(SDL_Surface* surface) {
    SDL_PixelFormat* format = surface->format;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_LockSurface(surface);
    for (int i = 1; i < surface->h - 1; i++) {
        for (int j = 1; j < surface->w - 1; j++) {
            Uint8* pixel = pix + i * p + j * bpp; //get current pixel
            //do thing
        }
    }
    SDL_UnlockSurface(surface);
    printf("blurring image sucess");
}


//comment to run project uncomment to run blurring()
int main(int argc, char* argv[]) {
    return EXIT_SUCCESS;
}
