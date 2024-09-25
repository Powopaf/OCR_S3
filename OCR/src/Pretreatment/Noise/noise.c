#include <SDL2/SDL.h>
#include <err.h>
#include <math.h>
///////////////////////
// to run noise only //
///////////////////////
#include "../Utils/sdl_utils.h"
////////////////////////////////
#define kernel_size 5
#define sigma 1.0



Uint8 Median(Uint8* pixel_list, int size) 
{
    //scans the 8 pixels around the pixel and return the median pixel
    for(int i = 0; i<size; i++)
    {
        for(int j = i + 1; j<size; j++)
        {
            if(pixel_list[i]>pixel_list[j])
            {
                Uint8 temp = pixel_list[i];
                pixel_list[i] = pixel_list[j];
                pixel_list[j] = temp;
            }
        }
    }

    return pixel_list[size/2];
}

void NoiseReduction(SDL_Surface *surface) 
{
    SDL_PixelFormat* format = surface->format;
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_LockSurface(surface);
    
    Uint8 pixel_list[9];

    //start at 1 and go to size - 1 for skip the border
    for(int j = 1; j < height - 1; j++) 
    {
        for(int i = 1; i < width - 1; i++) 
        {
            // Fill the pixel_list with the 8 pixels around the pixel
            int k = 0;
            for(int dj = -1; dj<=1; dj++)
            {
                for(int di = -1; di<=1; di++)
                {
                    Uint8* pixel = pix + (j+dj) * p + (i+di) * bpp;
                    Uint8 g = pixel[0];
                    pixel_list[k] = g;
                    k++;
                }
            }
            Uint8 newGrey = Median(pixel_list, 9);
            Uint8* pixel = pix + j * p + i * bpp;
            pixel[0] = newGrey;
            pixel[1] = newGrey;
            pixel[2] = newGrey;
        }
    }
    SDL_UnlockSurface(surface);
}

void NoiseReductionGaussian(SDL_Surface *surface) 
{
    SDL_PixelFormat* format = surface->format;
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_LockSurface(surface);
    
    // Noyau Gaussien 3x3 (sigma = 1.0)
    float kernel[3][3] = {
        {1.0 / 16, 2.0 / 16, 1.0 / 16},
        {2.0 / 16, 4.0 / 16, 2.0 / 16},
        {1.0 / 16, 2.0 / 16, 1.0 / 16}
    };

    //start at 1 and go to size - 1 for skip the border
    for (int j = 1; j < height - 1; j++) 
    {
        for (int i = 1; i < width - 1; i++) 
        {
            float sumGrey = 0.0f;

            // Appliquer le noyau 3x3 autour du pixel
            for (int dj = -1; dj <= 1; dj++)
            {
                for (int di = -1; di <= 1; di++)
                {
                    Uint8* pixel = pix + (j + dj) * p + (i + di) * bpp;
                    Uint8 g = pixel[0];  // On assume une image en niveaux de gris

                    sumGrey += g * kernel[dj + 1][di + 1];
                }
            }

            Uint8 newGrey = (Uint8)sumGrey;

            // Mettre à jour le pixel avec la nouvelle valeur
            Uint8* pixel = pix + j * p + i * bpp;
            pixel[0] = newGrey;
            pixel[1] = newGrey;
            pixel[2] = newGrey;
        }
    }
    
    SDL_UnlockSurface(surface);
}


//comment to run project uncomment to test greyscale
int main(int argc, char* argv[]) 
{
    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP("img.bmp");
    NoiseReduction(surface);
    NoiseReductionGaussian(surface);
    SDL_SaveBMP(surface, "imgNoise.bmp");
    SDL_FreeSurface(surface);
    sdl_close();
}
