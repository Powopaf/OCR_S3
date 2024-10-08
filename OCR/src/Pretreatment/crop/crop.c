#include <SDL2/SDL.h>
#include <err.h>
#include <unistd.h>

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
        char* arg[3] = { "../../Bash/rmAllBMP.sh", "4", NULL };
        execvp("../../Bash/rmAllBMP.sh", arg);
        errx(EXIT_FAILURE, "surface is NULL can't crop")
    }
    SDL_Surface* cropImage = SDL_CreateRGBSurfaceWithFormat(0, w, h, 24, SDL_PIXELFORMAT_RGB24);
    if (SDL_LockSurface(surface) < 0 || SDL_LockSurface(cropImage) < 0) {
        char* arg[3] = {"../../Bash/rmAllBMP.sh", "4", NULL };
        execvp("../../Bash/rmAllBMP.sh", arg);
        errx(EXIT_FAILURE, "Lock issue: %s", SDL_GetError)
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Uint8* pix_crop = cropImage->pixels + i * cropImage->pitch + j * cropImage->format->BytesPerPixel;
            Uint8* pix_base = pixel + i * surface->pitch + j * surface->format->BytesPerPixel;
            pix_crop[0] = pix_base[0];
            pix_crop[1] = pix_base[1];
            pix_crop[2] = pix_base[2];
        }
    }
    SDL_UnlockSurface(surface);
    SDL_UnlockSurface(cropImage);
    return cropImage;
}



//comment to run project uncomment to run crop()
/*int main(int argc, char* argv[]) {
    convert(argv[1]);
    SDL_Surface* surface = SDL_LoadBMP("img.bmp");
    SDL_Surface* c = crop(surface, surface->pixels, 256, 256);
    SDL_SaveBMP(c, "crop.bmp");
    SDL_FreeSurface(surface);
    SDL_FreeSurface(c);
    return EXIT_SUCCESS;
}*/
