#include <SDL2/SDL.h>
#include <err.h>

//#include "../Utils/sdl_utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "binarisation.h"

void binarisation(SDL_Surface *surface, int window_size, double k) 
{
    if(surface==NULL)
    {
        err(1,"ERROR: Surface NULL\n");
    }
    SDL_LockSurface(surface);

    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = surface->format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;

    int half_window = window_size / 2;
    double R = 128.0;
    
    int** Map = NULL;//Matrix for store the binarized_value
    MallocMatrix(&Map, height, width);

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
        SDL_UnlockSurface(surface);
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
    FreeMatrix(Map, height);
    SDL_UnlockSurface(surface);
}
//comment to run project uncomment to test greyscale
/*int main() {
    for(int i = 1; i<=7; i++)
    {
        printf("Proccessing img%i ...\n",i);
        char* file = NULL;
        char* save = NULL;

        asprintf(&file,"img/img%i.bmp",i);
        asprintf(&save,"img/img%iBin.bmp",i);

        sdl_setup();
        SDL_Surface* surface = SDL_LoadBMP(file); //convert() create a img.bmp
        if (surface == NULL)
        {
            err(1, "Unable to load image: %s\n", SDL_GetError());
        }
        binarisation(surface,21,0.35);
        SDL_SaveBMP(surface, save);
        SDL_FreeSurface(surface);
        sdl_close();
        free(file);
        free(save);
    }
}*/
