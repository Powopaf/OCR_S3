#include <SDL2/SDL.h>
#include <err.h>
#include <unistd.h>

//comment this include to run project uncomment to run blur.c
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"
//#include "../GreyScale/greyscale.h"
//////////////////////////////////////////////////////////////

void blurring(SDL_Surface* surface) {
    /*
     * this function should be use AFTER greyscale()
    */
    if (surface == NULL) {
        char* arg[3] = { "../../Bash/rmAllBMP.sh", "4", NULL };
        execvp("../../Bash/rmAllBMP.sh", arg);
        errx(EXIT_FAILURE, "surface is null can't blur");
    }
    SDL_PixelFormat* format = surface->format;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    int width = surface->w;
    int height = surface->h;
    if (SDL_LockSurface(surface) < 0) {
        char* arg[3] = { "../../Bash/rmAllBMP.sh", "4", NULL };
        execvp("../../Bash/rmAllBMP.sh", arg);
        errx(EXIT_FAILURE, "LockSurface issue: %s", SDL_GetError());
    }
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            Uint8* pixel = pix + i * p + j * bpp;
            Uint8 side_pixels[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
            //to access the pixel aroud the current
            side_pixels[0] = *(pixel - width * bpp - 3);    // 0 1 2
            side_pixels[1] = *(pixel - width * bpp);        // 3 c 4
            side_pixels[2] = *(pixel - width * bpp + 3);    // 5 6 7
            side_pixels[3] = *(pixel - 3);                  // [11,12,13] [21,22,23] [31,32,33]
            side_pixels[4] = *(pixel + 3);                  // [11,12,13] [21,22,23] [31,32,33]
            side_pixels[5] = *(pixel + width * bpp - 3);    // [11,12,13] [21,22,23] [31,32,33]
            side_pixels[6] = *(pixel + width * bpp);
            side_pixels[7] = *(pixel + width * bpp + 3);
            unsigned long  moy = 0;
            for (size_t i = 0; i < 8; i++) {
                moy = moy + (unsigned long)side_pixels[i];
            }
            moy = moy / 8;
            pixel[2] = (Uint8)moy;
        }
    }
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width; j++) {
            Uint8* pixel = pix + i * p + j * bpp;
            pixel[0] = pixel[2];
            pixel[1] = pixel[2];
        }
    }
    SDL_UnlockSurface(surface);
}
    


//comment to run project uncomment to run blurring()
/*int main(int argc, char* argv[]) {
    convert(argv[1]);
    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP("img.bmp");
    greyscale(surface);
    SDL_SaveBMP(surface, "grey.bmp");
    SDL_FreeSurface(surface);
    SDL_Surface* surf = SDL_LoadBMP("grey.bmp");
    blurring(surf);
    SDL_SaveBMP(surf, "blur.bmp");
    SDL_FreeSurface(surf);
    sdl_close();
    return EXIT_SUCCESS;
}*/
