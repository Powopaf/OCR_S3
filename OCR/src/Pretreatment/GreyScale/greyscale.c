#include <SDL2/SDL.h>
#include <err.h>
///////////////////////////
// to run greyscale only //
//////////////////////////

#include "../PretreatmentLib.h"
////////////////////////////////


void greyscale(SDL_Surface *surface) {
    SDL_PixelFormat* format = surface->format;
    int wigth = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    SDL_LockSurface(surface);
    Uint32* pix = surface->pixels;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < wigth; j++) {
            Uint8 r, g, b;
            SDL_GetRGB(pix[i * (p / 4) + j], format, &r, &g, &b);
            Uint8 grey = 0.2126 * r + 0.7152 * g + 0.0722 * b;
            pix[i * (p / 4) + j] = SDL_MapRGB(format, grey, grey, grey);
        }
    }
    SDL_UnlockSurface(surface);
}
//remove to run project un comment to test greyscale
int main(int argc, char* argv[]) {
    convert(argv[1]);
    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP("img.bmp"); //convert() create a img.bmp
    greyscale(surface);
    SDL_FreeSurface(surface);
    sdl_close();
}
