#include <SDL2/SDL.h>
#include "src/Pretreatment/Utils/sdl_utils.h"
#include "src/Pretreatment/Utils/convert.h"
#include "src/Pretreatment/GreyScale/greyscale.h"
#include "src/Pretreatment/Contrast/contrast.h"
#include "src/Pretreatment/Noise/gauss.h"
#include "src/Pretreatment/Noise/median.h"
#include "src/Pretreatment/Binarisation/binarisation.h"

int main(int argc, char* argv[]) {
    sdl_setup();
    convert(argv[1]);
    SDL_Surface* s = SDL_LoadBMP("img.bmp");
    greyscale(s);
    contrast(s);
    gauss(s);
    median(s);
    binarisation(s, 21, 0.35);
    SDL_SaveBMP(s, "a.bmp");
    SDL_FreeSurface(s);
    sdl_close();
    return EXIT_SUCCESS;
}
