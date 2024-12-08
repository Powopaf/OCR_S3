#include <SDL2/SDL.h>
#include <math.h>

void drawSolution(SDL_Surface *surface, int x1, int y1, int x2, int y2, int r, int g, int b) 
{
    //Radius of the line
    const int radius = 5;
    //Offset to extend the line
    const int offset = 10;

    SDL_LockSurface(surface); 
    SDL_PixelFormat* format = surface->format;
    
    //Vectors
    int dx = x2 - x1;
    int dy = y2 - y1;
    float length = sqrtf(dx * dx + dy * dy);
    float nx = (float)dx / length;
    float ny = (float)dy / length;
    
    //Extend the line
    x1 -= (int)(nx * offset);
    y1 -= (int)(ny * offset);
    x2 += (int)(nx * offset);
    y2 += (int)(ny * offset);
    
    //Draw the line
    for (float i = 0; i < length + 2 * offset; i++)
    {
        int cx = x1 + (int)(nx * i);
        int cy = y1 + (int)(ny * i);
        
        //Draw a circle around current point
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
                        int th = 100;

                        //If the pixel is bright enough, paint it
                        if(pixel[0]>th && pixel[1]>th && pixel[2]>th)
                        {
                            pixel[0] = r;
                            pixel[1] = g;
                            pixel[2] = b;
                        }
                    }
                }
            }
        }
    }
    SDL_UnlockSurface(surface);
}

