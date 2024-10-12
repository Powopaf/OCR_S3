#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    sdl_set_();
    convert(argv[1]);
    SDL_Surface* s = SDL_LoadBMP("img.bmp");
    greyscale(s);
    contrast(s);
    gauss(s);
    median(s);
    binarisation(s);
    SDL_SaveBMP(s, "a.bmp");
    SDL_FreeSurface(s);
    sdl_close();
    return EXIT_SUCCESS;
}
