#include <SDL2/SDL.h>
#include <err.h>

void greyscale(SDl_surface *surface) {
    SDL_PixelFormat* format = surface->format;
    int wigth = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    SDl_LockSurface(surface);
    Uint32* pix = surface->pixels;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            pix[i * (p / 4) + j] = SDL_MapRGB(format, r, g, b); // difine rgb
        }
    }
    SDL_UnlockSurface(surface);
}
