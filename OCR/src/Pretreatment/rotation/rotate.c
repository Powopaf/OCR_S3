#include "rotate.h"

///////////
//#include "../Utils/convert.h"
//#include "../Utils/sdl_utils.h"
////////////

#define M_PI       3.14159265358979323846

// Rotation using a rotation matrix (Best result)
SDL_Surface* rotation3(SDL_Surface *image, double angle) {
    SDL_LockSurface(image); // Lock the surface to directly access the pixel data
    
    // Get the image dimensions
    int width = image->w; // Get the with in pixel
    int height = image->h; // Get the height in pixel
    int bpp = image->format->BytesPerPixel; 
    int p = image->pitch;
    Uint8* pixels = (Uint8*)image->pixels; // Pointer to the pixel data

    double angle_radian = angle * M_PI / 180.0; //Convert the angle from degrees to radians

    double cos_angle = cos(angle_radian); 
    double sin_angle = sin(angle_radian);

    // Calculate the size of the new image after rotation (diagonal length of the original image)
    int new_w = sqrt((width*width)+(height*height))+1;
    int new_h = new_w;

    // Create a new surface for the rotated image
    SDL_Surface* rotated_image = SDL_CreateRGBSurfaceWithFormat(0, new_w, new_h, 24, image->format->format);
    Uint8* rotated_pixels = (Uint8*)rotated_image->pixels; // Pointer to the new image's pixels
    if (rotated_image == NULL)
    {
        fprintf(stderr, "Error creating rotated surface: %s\n", SDL_GetError());
        SDL_UnlockSurface(image);
        return NULL;
    }

    // Fill the entire surface with white (RGB: 255, 255, 255)
    SDL_FillRect(rotated_image, NULL, SDL_MapRGB(rotated_image->format, 255, 255, 255));

    int center_x = width / 2;
    int center_y = height / 2;
    int new_center_x = new_width / 2;
    int new_center_y = new_height / 2;

    // Loop over every pixel of the original image
    for (int y = 0; y < new_h; y++) 
    {
        for (int x = 0; x < new_w; x++) 
        {   // Coordinates of the pixel in the original image after rotation
            int old_x = (int)((x - new_center_x) * cos_angle + (y - new_center_y) * sin_angle) + center_x;
            int old_y = (int)(-(x - new_center_x) * sin_angle + (y - new_center_y) * cos_angle) + center_y;
            
            // Make sure the new coordinates are within bounds
            if (old_x >= 0 && old_x < width && old_y >= 0 && old_y < height)
            {   // Pointer to the pixel in the original image and in the rotated image
                Uint8* original_pixel = pixels + (old_y * p) + (old_x * bpp);
                Uint8* rotated_pixel = rotated_pixels + (y * rotated_image->pitch) + (x * rotated_image->format->BytesPerPixel);
                
                // Set the pixel color
                rotated_pixel[0] = original_pixel[0];
                rotated_pixel[1] = original_pixel[1];
                rotated_pixel[2] = original_pixel[2];
            }
        }
    }
    SDL_UnlockSurface(image); // Unlock when finish
    SDL_FreeSurface(image);  // Free the original surface if it's no longer needed

    return rotated_image;
}

// Rotation by shearing
SDL_Surface *rotation2(SDL_Surface* image, double angle) {
    SDL_LockSurface(image); // Lock the surface to directly access the pixel data
    
    // Get the image dimensions
    int width = image->w;
    int height = image->h;
    Uint8* pix = (Uint8*)image->pixels;
    int p = image->pitch;
    int bpp = image->format->BytesPerPixel;

    // Convert the angle from degrees to radians
    double angle_radian = -1*angle * (M_PI / 180.0);
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

                // Set the pixel color
                newp[0] = pixel[0];
                newp[1] = pixel[1];
                newp[2] = pixel[2];
            }
        }
    }

    SDL_UnlockSurface(image); // Unlock when finish
    SDL_FreeSurface(image);  // Free the original surface if it's no longer needed

                      

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
    SDL_LockSurface(image); //Lock the surface to directly access the pixel data
    
    //Get the image dimensions
    int width = image->w;
    int height = image->h;
    Uint8* pix = (Uint8*)image->pixels;
    int p = image->pitch;
    int bpp = image->format->BytesPerPixel;

    // Convert the angle from degrees to radians
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
                newp[0] = pixel[0];
                newp[1] = pixel[1];
                newp[2] = pixel[2];
            }
        }
    }

    SDL_UnlockSurface(image); // Unlock when finish
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