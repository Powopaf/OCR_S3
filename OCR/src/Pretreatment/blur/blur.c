#include <SDL2/SDL.h>
#include <err.h>

//comment this include to run project uncomment to run blur.c
#include "../Utils/convert.h"
#include "../Utils/sdl_utils.h"
#include "../GreyScale/greyscale.h"
//////////////////////////////////////////////////////////////

void blurring(SDL_Surface* surface) {
    /*
     * this function should be use AFTER greyscale()
    */
    SDL_PixelFormat* format = surface->format;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    int width = surface->w;
    int height = surface->h;
    SDL_LockSurface(surface);
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            int x = i * p;
            int y = j * bpp;
            Uint8* pixel = pix + x + y;
            Uint8 side_pixels[16] = { 0, 0, 0, 0, 0, 0, 0, 0 };
            //to access the pixel aroud the current
            side_pixels[0] =*(pixel - width * bpp - 1);   // 0 1 2
            side_pixels[1] =*(pixel - width * bpp);       // 3 c 4
            side_pixels[2] = *(pixel - width * bpp + 3);   // 5 8 7
            side_pixels[3] = *(pixel - 1);
            side_pixels[4] = *(pixel + 3);
            side_pixels[5] = *(pixel + width * bpp - 3);
            side_pixels[6] = (*pixel + width * bpp);
            side_pixels[7] = (*pixel + width * bpp + 1);
            Uint8 moy = 0;
            for (size_t i = 0; i < 8; i++) {
                moy = moy + side_pixels[i];
            }
            moy = moy / 8;
            pixel[0] = moy;
            pixel[1] = moy;
            pixel[2] = moy;
        }
    }
    SDL_UnlockSurface(surface);
}
    


//comment to run project uncomment to run blurring()
int main(int argc, char* argv[]) {
    convert(argv[1]);
    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP("img.bmp");
    //greyscale(surface);
    SDL_SaveBMP(surface, "blur.bmp");
    SDL_FreeSurface(surface);
    sdl_close();
    return EXIT_SUCCESS;
}
