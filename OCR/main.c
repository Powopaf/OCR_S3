#include <SDL2/SDL.h>
#include "main.h"
#include "src/Pretreatment/Utils/sdl_utils.h"
#include "src/Pretreatment/Utils/convert.h"
#include "src/Pretreatment/GreyScale/greyscale.h"
#include "src/Pretreatment/Contrast/contrast.h"
#include "src/Pretreatment/Noise/gauss.h"
#include "src/Pretreatment/Noise/median.h"
#include "src/Pretreatment/Binarisation/binarisation.h"
#include "src/Pretreatment/GridDetection/grid.h"

void Process(char* filename)
{
    sdl_setup();
    convert(filename);
    SDL_Surface* surface = SDL_LoadBMP("output/img.bmp");
    
    greyscale(surface);
    SDL_SaveBMP(surface,"output/imgGreyScale.bmp");

    //contrast(surface);
    SDL_SaveBMP(surface,"output/imgContrast.bmp");

    //gauss(surface);
    //median(surface);
    SDL_SaveBMP(surface,"output/imgNoiseReduction.bmp");

    binarisation(surface, 21, 0.35);
    SDL_SaveBMP(surface,"output/imgBinarisation.bmp");

    ProcessGrid(surface);
    SDL_SaveBMP(surface,"output/imgClusterFilter.bmp");

    //final treatment
    

    SDL_FreeSurface(surface);
    sdl_close();
}


