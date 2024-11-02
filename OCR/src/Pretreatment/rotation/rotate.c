#include "rotate.h"

///////////
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"
////////////

#define M_PI       3.14159265358979323846

// Rotation by rotation matrix (Best result)
SDL_Surface* rotation3(SDL_Surface *image, double angle) {
    SDL_LockSurface(image);
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
			



// Rotate an image with loss of pixels

                        new_y = round(new_x * (-1) * sin_angle + new_y); //second shear (inverted sinus sign)

                        new_x = round(new_x + new_y * tan_angle);//third shear (reverse)

                      

                        new_y += center_y;
                        new_x += center_x;
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

SDL_Surface *rotation1(SDL_Surface* image, double angle) {
    SDL_LockSurface(image);

    int width = image->w;
    int height = image->h;
    Uint8* pix = (Uint8*)image->pixels;
    int p = image->pitch;
    int bpp = image->format->BytesPerPixel;

    // Convert angle to radians
    double angle_radian = angle * (M_PI / 180.0);
    double sin_angle = sin(angle_radian);
    double cos_angle = cos(angle_radian);

    // New surface dimensions to fit the rotated image
    int new_w = sqrt((width*width)+(height*height))+1;
    int new_h = new_w;
    int center_x = new_w / 2;
    int center_y = new_h / 2;

    SDL_Surface* rotated_image = SDL_CreateRGBSurfaceWithFormat(0, new_w, new_h, 24, image->format->format);
    if (!rotated_image) {
        fprintf(stderr, "Error creating rotated surface: %s\n", SDL_GetError());
        SDL_UnlockSurface(image);
        return NULL;
    }
    
    // Fill the entire surface with white (RGB: 255, 255, 255)
    SDL_FillRect(rotated_image, NULL, SDL_MapRGB(rotated_image->format, 255, 255, 255));

    Uint8* pix_r = (Uint8*)rotated_image->pixels;
    int protate = rotated_image->pitch;

    // Loop over every pixel of the original image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Current pixel in the original image
            Uint8* pixel = pix + i * p + j * bpp;

            // Offset from the center of the original image
            int x_off = j - width / 2;
            int y_off = i - height / 2;

            int new_x = round(cos_angle * x_off - sin_angle * y_off);
            int new_y = round(sin_angle * x_off + cos_angle * y_off);

            // Translate the new coordinates to the center of the new image
            new_x += center_x;
            new_y += center_y;

            // Make sure the new coordinates are within bounds
            if (new_x >= 0 && new_x < new_w && new_y >= 0 && new_y < new_h) {
                Uint8* newp = pix_r + new_y * protate + new_x * rotated_image->format->BytesPerPixel;

                // Set the pixel color
                newp[0] = pixel[0];  // Red
                newp[1] = pixel[1];  // Green
                newp[2] = pixel[2];  // Blue
            }
        }
    }

    SDL_UnlockSurface(image);
    SDL_FreeSurface(image);  // Free the original surface if it's no longer needed

    return rotated_image;
}

void rotation(char* filename, double angle, char* outputPath)
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