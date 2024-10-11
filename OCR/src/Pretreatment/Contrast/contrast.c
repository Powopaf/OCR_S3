#include <SDL2/SDL.h>

//comment to run project, uncomment to run contrast
#include "../Utils/convert.h"
#include "../Utils/sdl_utils.h"
#include "../GreyScale/greyscale.h"


void contrast(SDL_Surface* surface) {
    const Uint8 max_intensity = 0;
    const Uint8 min_intensity = 255;
    int width = surface->w;
    int height = surface->h;
    int bpp = surface->format->BytesPerPixel;
    SDL_LockSurface(surface);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //current pixel
            Uint8* pixel = surface->pixels + i * surface->pitch + j * bpp;
            /*Uint8* side_pixel[8];
            side_pixels[0] = *(pixel - width * bpp - 3);    // 0 1 2
            side_pixels[1] = *(pixel - width * bpp);        // 3 c 4
            side_pixels[2] = *(pixel - width * bpp + 3);    // 5 6 7
            side_pixels[3] = *(pixel - 3);                  // [11,12,13] [21,22,23] [31,32,33]
            side_pixels[4] = *(pixel + 3);                  // [11,12,13] [21,22,23] [31,32,33]
            side_pixels[5] = *(pixel + width * bpp - 3);    // [11,12,13] [21,22,23] [31,32,33]
            side_pixels[6] = *(pixel + width * bpp);
            side_pixels[7] = *(pixel + width * bpp + 3);*/
            pixel[2] = 255 * ((pixel[0] - min_intensity) / (max_intensity - min_intensity));
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Uint8* pixel = surface->pixels + i * surface->pitch + j * bpp;
            pixel[0] = pixel[2];
            pixel[1] = pixel[2];
        }
    }
    SDL_UnlockSurface(surface);
}


//comment to run project, uncomment to run contrast
int main(int argc, char* argv) {
    return EXIT_SUCCESS;
}
