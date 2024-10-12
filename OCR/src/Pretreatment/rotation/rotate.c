#include "rotate.h"

///////////
#include "../Utils/convert.h"
#include "../Utils/sdl_utils.h"
////////////

// Rotation by rotation matrix (Best result)
SDL_Surface* rotation3(SDL_Surface* image, double angle)
{
    int width = image->w;
    int height = image->h;
    int bpp = image->format->BytesPerPixel;
    int p = image->pitch;
    Uint8* pixels = (Uint8*)image->pixels;

    double angle_radian = angle * M_PI / 180.0;

    double cos_angle = cos(angle_radian);
    double sin_angle = sin(angle_radian);

    int new_width = width * 2;
    int new_height = height * 2;

    SDL_Surface* rotated_image = SDL_CreateRGBSurfaceWithFormat(0, new_width, new_height, 24, SDL_PIXELFORMAT_RGB24);
    Uint8* rotated_pixels = (Uint8*)rotated_image->pixels;

    int center_x = width / 2;
    int center_y = height / 2;
    int new_center_x = new_width / 2;
    int new_center_y = new_height / 2;

    for (int y = 0; y < new_height; y++) 
    {
        for (int x = 0; x < new_width; x++) 
        {
            int old_x = (int)((x - new_center_x) * cos_angle + (y - new_center_y) * sin_angle) + center_x;
            int old_y = (int)(-(x - new_center_x) * sin_angle + (y - new_center_y) * cos_angle) + center_y;

            if (old_x >= 0 && old_x < width && old_y >= 0 && old_y < height)
            {
                Uint8* original_pixel = pixels + (old_y * p) + (old_x * bpp);

                Uint8* rotated_pixel = rotated_pixels + (y * rotated_image->pitch) + (x * rotated_image->format->BytesPerPixel);
                rotated_pixel[0] = original_pixel[0];
                rotated_pixel[1] = original_pixel[1];
                rotated_pixel[2] = original_pixel[2];
            }
        }
    }

    return rotated_image;
}

// Rotation by shearing
SDL_Surface *rotation2(SDL_Surface* image, double angle)
{
        int width = image->w;
        int height = image->h;
	Uint8* pix = image->pixels;
	int p = image->pitch;
	int bpp = image->format->BytesPerPixel;
	
	// Convert angle to radian
        double angle_radian = angle * (M_PI / 180.0);
        int center_x = width / 2;
        int center_y = height / 2;
        double sin_angle = sin(angle_radian);
        double tan_angle = tan(angle_radian / 2);

        SDL_Surface* rotated_image = SDL_CreateRGBSurfaceWithFormat(0, width * 2, height * 2, 24, SDL_PIXELFORMAT_RGB24);
	int protate = rotated_image->pitch;
	Uint8* pix_r = rotated_image->pixels;
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
			Uint8* pixel = pix + i * p + j * bpp; //get current pixel
			
                        double xOff = i - center_y; //offsets from the center of the image
                        double yOff = j - center_x;

                        int new_x = round(xOff + yOff * tan_angle); //first shear (reverse)
                        int new_y = round(yOff);
			
			new_y = round(new_x * (-1) * sin_angle + new_y); //second shear (inverted sinus sign)

			new_x = round(new_x + new_y * tan_angle);//third shear (reverse)

			new_y += center_y;
			new_x += center_x;
			
                        // Checks if the position is within the bounds of the original image
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


// Rotate an image with loss of pixels
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

// Test of the function
int main(int argc, char* argv[]) {
	convert(argv[1]);
    	sdl_setup();
    	SDL_Surface* surface = SDL_LoadBMP("img.bmp"); //convert() create a img.bmp
    	SDL_Surface* a = rotation3(surface, 450.0);
    	SDL_SaveBMP(a, "img.bmp");
    	SDL_FreeSurface(surface);
	SDL_FreeSurface(a);
    	sdl_close();
}
