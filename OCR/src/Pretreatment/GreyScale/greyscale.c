#include <SDL2/SDL.h>
#include <err.h>
///////////////////////////
// to run greyscale only //
//////////////////////////

#include "../Utils/convert.h"
#include "../Utils/sdl_utils.h"
////////////////////////////////


void greyscale(SDL_Surface *surface) {
    SDL_PixelFormat* format = surface->format;
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    SDL_LockSurface(surface);
    Uint8* pix = surface->pixels;
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8 r, g, b;
            SDL_GetRGB(pix[j * p + i + bpp], format, &r, &g, &b);
            Uint8 grey = 0.2126 * r + 0.7152 * g + 0.0722 * b;
            pix[j * p + i + bpp] = SDL_MapRGB(format, grey, grey, grey);
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
