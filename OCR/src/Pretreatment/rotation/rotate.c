#include "rotate.h"

///////////
#include "../Utils/convert.h"
#include "../Utils/sdl_utils.h"
////////////


// Rotation de l’image
SDL_Surface *rotation(SDL_Surface* image, double angle)
{
        int width = image->w;
        int height = image->h;
	Uint8* pix = image->pixels;
	int p = image->pitch;
	int bpp = image->format->BytesPerPixel;

        double angle_radian = angle * (M_PI / 180.0);
        int center_x = width / 2;
        int center_y = height / 2;
        double cos_angle = cos(angle_radian);
        double sin_angle = sin(angle_radian);
        SDL_Surface* rotated_image = SDL_CreateRGBSurfaceWithFormat(0, width * 2, height * 2, 24, SDL_PIXELFORMAT_RGB24);
	int protate = rotated_image->pitch;
	Uint8* pix_r = rotated_image->pixels;
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
			Uint8* pixel = pix + i * p + j * bpp; //get current pixel
                        double xOff = i - center_y;
                        double yOff = j - center_x;
                        int new_x = round(xOff * cos_angle + yOff * sin_angle + center_x);
                        int new_y = round(yOff * cos_angle - xOff * sin_angle + center_y);

                        if (1 || (0 <= new_x && new_x < width && 0 <= new_y && new_y < height))
                        {
				Uint8* newp = pix_r + (new_x+center_x/2) * protate + (new_y+center_y/2) * rotated_image->format->BytesPerPixel;
				newp[0] = pixel[0];
				newp[1] = pixel[1];
				newp[2] = pixel[2];
			}
		}
	}
	return rotated_image;		
}

// Tester la fonction
int main(int argc, char* argv[]) {
	convert(argv[1]);
    	sdl_setup();
    	SDL_Surface* surface = SDL_LoadBMP("img.bmp"); //convert() create a img.bmp
    	SDL_Surface* a = rotation(surface, 17.0);
    	SDL_SaveBMP(a, "img.bmp");
    	SDL_FreeSurface(surface);
	SDL_FreeSurface(a);
    	sdl_close();
}
