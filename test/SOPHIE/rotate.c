#include "rotate.h"


Uint8 getPixel(SDL_Surface *surface,int x, int y) 
{
	Uint8 *pixels = (Uint8 *)surface->pixels;
	return pixels[(y * surface->w) + x];
}

void setPixel(SDL_Surface *surface, int x, int y, Uint8 pixel) 
{
	Uint8 *pixels = (Uint8 *)surface->pixels;
	pixels[(y * surface->w) + x] = pixel;
}

SDL_Surface *rotation(SDL_Surface *image, double angle)
{
	int width = image->w;
	int height = image->h;
	double angle_radian = angle * (M_PI / 180.0);
	int center_x = width / 2;
	int center_y = height / 2;
	double cos_angle = cos(angle_radian);
	double sin_angle = sin(angle_radian);
	SDL_Surface *rotated_image = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, image->format->format);

	for (int x = 0; x < width; x++) 
	{
        	for (int y = 0; y < height; y++) 
		{
            		double xOff = x - center_x;
            		double yOff = y - center_y;
            		int new_x = round(xOff * cos_angle + yOff * sin_angle + center_x);
            		int new_y = round(yOff * cos_angle - xOff * sin_angle + center_y);

            		if (0 <= new_x && new_x < width && 0 <= new_y && new_y < height) 
			{
             	   		Uint8 pixel = getPixel(image, x, y);
                		setPixel(rotated_image, new_x, new_y, pixel);
            		}
        	}
	}
	return rotated_image;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image initialization failed: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Image Rotation",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *screen_surface = SDL_GetWindowSurface(window);

    SDL_Surface *image = IMG_Load("donkey.png"); 
    if (!image) {
        printf("Image loading failed: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *rotated_image = rotation(image, 90.0);  

    SDL_BlitSurface(rotated_image, NULL, screen_surface, NULL);
    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);

    SDL_FreeSurface(rotated_image);
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

