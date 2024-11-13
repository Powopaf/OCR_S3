#include <SDL2/SDL.h>
#include <err.h>
#include <unistd.h>

///////////////////////////
// to run greyscale only //
//////////////////////////
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"
////////////////////////////////


void greyscale(SDL_Surface* surface) {
    
    // error handling
    if (surface == NULL) {
        errx(EXIT_FAILURE, "surface is NULL can't apply greyscale");
    }

    //init variable to check each pixels
    SDL_PixelFormat* format = surface->format; // get the format
    int width = surface->w; // get the with in pixel
    int height = surface->h; // get the height in pixel
    int p = surface->pitch; // get the width * BytesPerPixel 
    int bpp = format->BytesPerPixel; // get the BYtePerPixel aka 3 with the bmp
    Uint8* pix = (Uint8*)surface->pixels; // pointer to the very first pixel of
                                          // the image
                                          // pix = r
                                          // pix + 1 = g
                                          // pix + 2 = b
                                          // pix + 3 = next pixel red color and
                                          // so on
    
    //lock to protect memory with error handling
    if (SDL_LockSurface(surface) < 0) {
        errx(EXIT_FAILURE, "SDL_LockSurface fail:  %s", SDL_GetError());
    }
    
    // loop through the image
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8* pixel = pix + j * p + i * bpp; // magic line
            Uint8 grey = 0.212671f * pixel[0] + 0.715160f * pixel[1] + 0.072169f * pixel[2]; // formula to turn the color in gray
            pixel[0] = grey;
            pixel[1] = grey;
            pixel[2] = grey;
        }
    }
    
    //unlock when finish
    SDL_UnlockSurface(surface);
}
//comment to run project uncomment to test greyscale
/*int main(int argc, char* argv[]) {
    convert(argv[1]);
    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP("img.bmp"); //convert() create a img.bmp
    greyscale(surface);
    SDL_SaveBMP(surface, "img.bmp");
    SDL_FreeSurface(surface);
    sdl_close();

}*/
