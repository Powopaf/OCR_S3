#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void drawSolution(SDL_Surface *surface, int x1, int y1, int x2, int y2, int r, int g, int b) 
{
    const int radius = 5;

    SDL_LockSurface(surface);

    int dx = x2 - x1;
    int dy = y2 - y1;
    float length = sqrtf(dx * dx + dy * dy);
    float nx = (float)dx / length;
    float ny = (float)dy / length;
    
    SDL_PixelFormat* format = surface->format;

    for (float i = 0; i < length; i++)
    {
        int cx = x1 + (int)(nx * i);
        int cy = y1 + (int)(ny * i);

        for (int rx = -radius; rx <= radius; rx++)
        {
            for (int ry = -radius; ry <= radius; ry++)
            {
                if (rx * rx + ry * ry <= radius * radius)
                {
                    int px = cx + rx;
                    int py = cy + ry;

                    if (px >= 0 && px < surface->h && py >= 0 && py < surface->w)
                    {
                        int p = surface->pitch;
                        int bpp = format->BytesPerPixel;
                        Uint8* pixels = (Uint8*)surface->pixels;
                        Uint8* pixel = pixels + px * p + py * bpp;
                        int th = 50;
                        if(pixel[0]>th && pixel[1]>th && pixel[2]>th)
                        {
                            pixel[0] = r;
                            pixel[1] = g;
                            pixel[2] = b;
                        }
                        
                        //
                    }
                }
            }
        }
    }
    SDL_UnlockSurface(surface);
}

/*
int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Draw Line Test", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(win);
    if (!surface) {
        printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Fill the screen with white
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    // Draw a red line
    drawSolution(surface, 100, 100, 500, 400, 255, 0, 0);

    // Update the window
    SDL_UpdateWindowSurface(win);

    // Wait for 5 seconds
    SDL_Delay(5000);

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
*/
