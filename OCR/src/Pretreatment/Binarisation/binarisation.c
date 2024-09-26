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
    double R = 100.0;
    
    int Map[height][width];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Variables pour calculer la moyenne et l'écart-type local
            int sum = 0;
            int sq_sum = 0;
            int count = 0;

            // Parcours de la fenêtre autour du pixel (x, y)
            for (int wy = -half_window; wy <= half_window; wy++) {
                for (int wx = -half_window; wx <= half_window; wx++) {
                    int ny = y + wy;
                    int nx = x + wx;

                    // Vérifier que la position est dans les limites de l'image
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        Uint8* pixel = pix + ny * p + nx * bpp;
                        Uint8 intensity = pixel[0]; // On suppose que l'image est déjà en niveaux de gris
                        sum += intensity;
                        sq_sum += intensity * intensity;
                        count++;
                    }
                }
            }

            // Calcul de la moyenne et de l'écart-type local
            double mean = sum / (double)count;
            double variance = (sq_sum / (double)count) - (mean * mean);
            double stddev = sqrt(variance);

            // Calcul du seuil de Sauvola pour ce pixel
            double threshold = mean * (1 + k * ((stddev / R) - 1));
            
            // Appliquer le seuil
            Uint8* pixel = pix + y * p + x * bpp;
            Uint8 intensity = pixel[0];
            int binarized_value = (intensity > threshold) ? 0 : 255;
            
            Map[y][x] = binarized_value;

        }
    }

    //apply binarized_values
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
    binarisation_sauvola(surface,25,0.05);
    SDL_SaveBMP(surface, "imgBin.bmp");
    SDL_FreeSurface(surface);
    sdl_close();
}
