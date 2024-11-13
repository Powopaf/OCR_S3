#include <SDL2/SDL.h>

void contrast(SDL_Surface* surface) {
    // init image loop
    int width = surface->w;
    int height = surface->h;
    int bpp = surface->format->BytesPerPixel;
    SDL_LockSurface(surface);
    
    for (int i = 1; i < height - 1; i++) {
     
        for (int j = 1; j < width - 1; j++) {
            //current pixel
            Uint8* pixel = (Uint8*)surface->pixels + i * surface->pitch + j * bpp;
            Uint8 side_pixel[8];
            // we only look at the red color since r=g=b then we modify the r
            // value
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
    // set r to the g and b value
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Uint8* pixel = (Uint8*)surface->pixels + i * surface->pitch + j * bpp;
            pixel[0] = pixel[2];
            pixel[1] = pixel[2];
        }
    }
    SDL_UnlockSurface(surface);
}
