#include <SDL2/SDL.h>
#include <err.h>

#include "../Utils/sdl_utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void binarisation_sauvola(SDL_Surface *surface, int window_size, double k) {
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = surface->format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_LockSurface(surface);

    int half_window = window_size / 2;
    double R = 128.0;
    
    int Map[height][width];//Matrix for store the binarized_value

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //sum variable for the Sauvolo formula
            int sum = 0;
            int sq_sum = 0;
            int count = 0;

            // Get all the pixel around the current pixel
            for (int wy = -half_window; wy <= half_window; wy++) {
                for (int wx = -half_window; wx <= half_window; wx++) {
                    int ny = y + wy;
                    int nx = x + wx;

                    // Verify if the pixel is in the image
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        Uint8* pixel = pix + ny * p + nx * bpp;
                        Uint8 intensity = pixel[0]; // get the intensity of the pixel
                        sum += intensity;
                        sq_sum += intensity * intensity;
                        count++;
                    }
                }
            }
            // calculates local mean and standard deviation
            double mean = sum / (double)count;
            double variance = (sq_sum / (double)count) - (mean * mean);
            double stddev = sqrt(variance);

            // Compute the Sauvola formula for the current pixel
            double threshold = mean * (1 + k * ((stddev / R) - 1));
            
            // Apply the threshold
            Uint8* pixel = pix + y * p + x * bpp;
            Uint8 intensity = pixel[0];
            int binarized_value = (intensity > threshold) ? 0 : 255;
            
            Map[y][x] = binarized_value;//store the binarized value of the pixel
        }
    }
    //apply the binarized values
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8* pixel = pix + j * p + i * bpp; // magic line
            Uint8 color = Map[j][i];
            pixel[0] = color;
            pixel[1] = color;
            pixel[2] = color;
        }
    }

    SDL_UnlockSurface(surface);
}

//comment to run project uncomment to test greyscale
int main(int argc, char* argv[]) {
    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP(argv[1]); //convert() create a img.bmp
    binarisation_sauvola(surface,15,0.05);
    SDL_SaveBMP(surface, "imgBin.bmp");
    SDL_FreeSurface(surface);
    sdl_close();
}
