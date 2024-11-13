#include <SDL2/SDL.h>
#include <err.h>
#include <unistd.h>
#include "crop.h"
//comment to run project uncomment to run crop()
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"

SDL_Surface* crop(SDL_Surface* surface, Uint8* pixel, int w, int h) {
    /*
     * surface -> surface of the we want to crop
     * pixel -> coord xy of the top left corner
     * w -> width of the CROP PHOTO
     * h -> height of the CROP PHOTO
     * !!!!
     * THE SURFACE WE WANT TO CROP MUST HAVE VALID COORD 
     * ELSE MAYBE SEGFAULT OR WRONG PIXEL IN THE CROP IMAGE
     * !!!!
     * the return surface should be save as a .bmp image in a folder with a
     * specific name
    */
    if (surface == NULL) {
        errx(EXIT_FAILURE, "surface is NULL can't crop");
    }
    SDL_Surface* cropImage = SDL_CreateRGBSurfaceWithFormat(0, w, h, 24, SDL_PIXELFORMAT_RGB24);
    if (SDL_LockSurface(surface) < 0 || SDL_LockSurface(cropImage) < 0) {
        errx(EXIT_FAILURE, "Lock issue: %s", SDL_GetError());
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Uint8* pix_crop = (Uint8*)cropImage->pixels + i * cropImage->pitch + j * cropImage->format->BytesPerPixel;
            Uint8* pix_base = (Uint8*)pixel + i * surface->pitch + j * surface->format->BytesPerPixel;
            pix_crop[0] = pix_base[0];
            pix_crop[1] = pix_base[1];
            pix_crop[2] = pix_base[2];
        }
    }
    SDL_UnlockSurface(surface);
    SDL_UnlockSurface(cropImage);
    return cropImage;
}

SDL_Surface* cropLetter(Shape* shape, int** Map)
{
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, shape->w, shape->h, 24,SDL_PIXELFORMAT_RGB24);
    
    SDL_LockSurface(surface);
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_PixelFormat* format = surface->format;
    int bpp = format->BytesPerPixel;
    int p = surface->pitch;

    int id = shape->id;
    for(int j = shape->Minj; j<=shape->Maxj; j++)
    {
        for(int i = shape->Mini; i<=shape->Maxi; i++)
        {
            if(Map[j][i]==id)
            {
                int cropj = j-shape->Minj;
                int cropi = i-shape->Mini;
                Uint8* pixel = pix + cropj * p + cropi * bpp;
                pixel[0] = 255;
                pixel[1] = 255;
                pixel[2] = 255;
            }
        }
    }
    SDL_UnlockSurface(surface);
    return surface;
}
