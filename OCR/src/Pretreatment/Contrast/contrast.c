#include <SDL2/SDL.h>

//comment to run project, uncomment to run contrast
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"
//#include "../GreyScale/greyscale.h"


void contrast(SDL_Surface* surface) {
    int width = surface->w;
    int height = surface->h;
    int bpp = surface->format->BytesPerPixel;
    SDL_LockSurface(surface);
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            //current pixel
            Uint8* pixel = (Uint8*)surface->pixels + i * surface->pitch + j * bpp;
            Uint8 side_pixel[8];
            side_pixel[0] = *(pixel - width * bpp - 3);    // 0 1 2
            side_pixel[1] = *(pixel - width * bpp);        // 3 c 4
            side_pixel[2] = *(pixel - width * bpp + 3);    // 5 6 7
            side_pixel[3] = *(pixel - 3);                  // [11,12,13] [21,22,23] [31,32,33]
            side_pixel[4] = *(pixel + 3);                  // [11,12,13] [21,22,23] [31,32,33]
            side_pixel[5] = *(pixel + width * bpp - 3);    // [11,12,13] [21,22,23] [31,32,33]
            side_pixel[6] = *(pixel + width * bpp);
            side_pixel[7] = *(pixel + width * bpp + 3);
            for (size_t k = 0; k < 8; k++) {
                if (side_pixel[k] < pixel[0] && pixel[0] < 200) {
                    pixel[2] = pixel[2] - 50 < 0 ? 0 : pixel[2] - 50;
                }
            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Uint8* pixel = (Uint8*)surface->pixels + i * surface->pitch + j * bpp;
            pixel[0] = pixel[2];
            pixel[1] = pixel[2];
        }
    }
    SDL_UnlockSurface(surface);
}


//comment to run project, uncomment to run contrast
/*int main(int argc, char* argv[]) {
    convert(argv[1]);
    sdl_setup();
    SDL_Surface* s = SDL_LoadBMP("img.bmp");
    greyscale(s);
    SDL_SaveBMP(s, "c.bmp");
    SDL_Surface* s1 = SDL_LoadBMP("c.bmp");
    contrast(s1);
    SDL_SaveBMP(s1, "c.bmp");
    SDL_FreeSurface(s1);
    SDL_FreeSurface(s);
    sdl_close();
    return EXIT_SUCCESS;
}*/
