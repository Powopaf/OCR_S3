#include <SDL2/SDL.h>1
#include "src/Preatrement/Utils/sdl_utils.h"
#include "src/Preatrement/Utils/convert.h"
#include "src/Preatrement/GreyScale/greyscale.h"
#include "src/Preatrement/Contrast/contrast.h"
#include "src/Preatrement/Noise/gauss.h"
#include "src/Preatrement/Noise/median.h"
#include "src/Preatrement/Binarisation/binarisation.h"

int main(int argc, char* argv[]) {
    sdl_setup();
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
