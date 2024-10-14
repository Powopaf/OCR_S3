#include <SDL2/SDL.h>
#include <err.h>
#include <unistd.h>
#include <math.h>

//comment to run project uncomment to run noise reduction functions
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"
//#include "../GreyScale/greyscale.h"
//#include "../blur/blur.h"
//#include "median.h"
//////////////////////////////////////////////////////////////////////

double gFunc(int x, int y) {
    /*
     * gaussian funtion see gaussian blur for definition
    */
    const double sig = 2.0;
    double part1 = 1 / (2 * M_PI * sig * sig);
    double power = -(x * x + y * y) / (2 * sig * sig);
    double part2 = exp(power);
    return part1 * part2;
}

void gauss(SDL_Surface* surface) {
    /*
     * G(x,y) = (1/2*pi*sig^2)*(exp^(-(x^2 + y^2/2*sig^2)))
     * with x, y the neighboring pixel
     * sig = 1.5
     * the kernel is : ->size of 5x5
     * (-2, 2) (-1, 2) (0, 2) (1, 2) (2, 2)
     * (-2, 1) (-1, 1) (0, 1) (1, 1) (2, 1)
     * (-2, 0) (-1, 0) (0, 0) (1, 0) (2, 0)
     * (-2,-1) (-1,-1) (0,-1) (1,-1) (2,-1)
     * (-2,-2) (-1,-2) (0,-2) (1,-2) (2,-2)
     * we just aply G(x,y) on each coordinate above
     * !!!!
     * THE IMAGE MUST HAVE WENT THROUGH THE GREYSCALE BEFORE THIS ONE!!!!
     * !!!!
     */
    /*double kernel[5][5] = {
        { gFunc(-2, 2), gFunc(-1, 2), gFunc(0, 2), gFunc(1, 2), gFunc(2, 2) },
        { gFunc(-2, 1), gFunc(-1, 1), gFunc(0, 1), gFunc(1, 1), gFunc(2, 1) },
        { gFunc(-2, 0), gFunc(-1, 0), gFunc(0, 0), gFunc(1, 0), gFunc(2, 0) },
        { gFunc(-2,-1), gFunc(-1,-1), gFunc(0,-1), gFunc(1,-1), gFunc(2,-1) },
        { gFunc(-2,-2), gFunc(-1,-2), gFunc(0,-2), gFunc(1,-2), gFunc(2,-2) }
    };*/
    double kernel[3][3] = {
        { gFunc(-1, 1), gFunc(0, 1), gFunc(1, 1) },
        { gFunc(-1, 0), gFunc(0, 0), gFunc(1, 0) },
        { gFunc(-1,-1), gFunc(0,-1), gFunc(1,-1) }
    };
    // we don't go in pixel near the ledge
    SDL_LockSurface(surface);
    for (int i = 1; i < surface->h - 1; i++) {
        for (int j = 1; j < surface->w - 1; j++) {
            //curent pixel
            Uint8* pixel = surface->pixels + i * surface->pitch + j * surface->format->BytesPerPixel;
            
            double sum_color = 0.0;
            int p1 = -1;
            int p2 = 1;
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    sum_color = sum_color + kernel[ki][kj] * (double)(pixel + p2 * surface->pitch + p1 * surface->format->BytesPerPixel)[0];
                    p1++;
                }
                p2--;
            }
            pixel[0] = (Uint8)sum_color;
            pixel[1] = (Uint8)sum_color;
            pixel[2] = (Uint8)sum_color;
        }
    }
    SDL_UnlockSurface(surface);
}

//comment to run project uncomment to run noise reduction function
/*int main(int argc, char* argv[]) {

    sdl_setup();
    
    convert(argv[1]);
    SDL_Surface* surface = SDL_LoadBMP("img.bmp");
    greyscale(surface);
    SDL_SaveBMP(surface, "img.bmp");
    SDL_FreeSurface(surface);
    
    SDL_Surface* s0 = SDL_LoadBMP("img.bmp");
    contrast(s0);
    SDL_SaveBMP(s0, "img.bmp");
    SDL_FreeSurface(s0);
    
    SDL_Surface* s = SDL_LoadBMP("img.bmp");
    gaussianBlur(s);
    SDL_SaveBMP(s, "gauss1.bmp");
    SDL_FreeSurface(s);
    
    SDL_Surface* s2 = SDL_LoadBMP("gauss1.bmp");
    median(s2);
    SDL_SaveBMP(s2, "gauss2.bmp");
    SDL_FreeSurface(s2);
    
    //SDL_Surface* s3 = SDL_LoadBMP("gauss2.bmp");
    //blurring(s3);
    //SDL_SaveBMP(s3, "gauss3.bmp");
    //SDL_FreeSurface(s3);
    
    sdl_close();
    return EXIT_SUCCESS;
}*/
