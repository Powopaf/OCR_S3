#include <SDL2/SDL.h>
#include <err.h>

///////////////////////////
// to run greyscale only //
//////////////////////////
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"
////////////////////////////////


void greyscale(SDL_Surface *surface) {
    
    //init variable to check each pixels
    SDL_PixelFormat* format = surface->format;
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    
    //lock to protect memory
    SDL_LockSurface(surface);
    
    //inside the imgae (.bmp)
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8* pixel = pix + j * p + i * bpp; // magic line
            Uint8 grey = 0.212671f * pixel[0] + 0.715160f * pixel[1] + 0.072169f * pixel[2];
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
