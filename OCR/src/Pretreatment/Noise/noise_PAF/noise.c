#include <SDL2/SDL.h>
#include <err.h>
#include <unistd.h>
#include <math.h>

double gFunc(int x, int y, double sig) {
    /*
     * gaussian funtion see gaussian blur for definition
    */
    double part1 = 1 / (2 * M_PI * sig * sig);
    double power = -(x * x + y * y) / (2 * sig * sig);
    double part2 = exp(power);
    return part1 * part2;
}


void gaussianBlur(SDL_Surface* surface) {
    /*
     * G(x,y) = (1/2*pi*sig^2)*(exp^(-(x^2 + y^2/2*sig^2)))
     * with x, y the neighboring pixel
     * sig = 1.5
     * the kernel is :
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
    double kernel[5][5] = {
        { gFunc(-2, 2), gFunc(-1, 2), gFunc(0, 2), gFunc(1, 2), gFunc(2, 2) },
        { gFunc(-2, 1), gFunc(-1, 1), gFunc(0, 1), gFunc(1, 1), gFunc(2, 1) },
        { gFunc(-2, 0), gFunc(-1, 0), gFunc(0, 0), gFunc(1, 0), gFunc(2, 0) },
        { gFunc(-2,-1), gFunc(-1,-1), gFunc(0,-1), gFunc(1,-1), gFunc(2,-1) },
        { gFunc(-2,-2), gFunc(-1,-2), gFunc(0,-2), gFunc(1,-2), gFunc(2,-2) }
    };
    // we don't go in pixel near the ledge
    SDL_LockSurface(surface);
    for (int i = 2, i < surface->height - 2; i++) {
        for (int j = 2; j < surface->width - 2; j++) {
            double newcolor;
            //curent pixel
            Uint8* pixel = surface->pixels + i * surface->pitch + j * surface->format->BytesPerPixel;
            double sum_color = 0.0;
            int p1 = -2;
            int p2 = 2;
            for (int ki = 0; ki < 5; ki++) {
                for (int kj = 0; kj < 5; kj++) {
                    sum_color = sum_color + kernel[ki][kj] * (pixel + p1 * surface->pitch  + p2 * surface->height * surface->format->BytesPerPixel);
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
