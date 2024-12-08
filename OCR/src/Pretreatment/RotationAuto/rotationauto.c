#include "rotationauto.h"

// Simpler version of CreateShape
Shape* CreateShape(int id, int x, int y) {
    Shape* shape = (Shape*)malloc(sizeof(Shape));
    shape->id = id;
    shape->Cx = x;
    shape->Cy = y;
    shape->w = 100;  // Default width
    shape->h = 200;  // Default height
    return shape;
}

// Calculate the orientation of a shape
double calculateOrientation(Shape* shape) {
    double width = shape->w;
    double height = shape->h;
    double angle = 0;

    if (width > height) 
    {
        angle = atan2(height, width);  // Horizontal alignment
    } else 
    {
        angle = atan2(width, height);  // Vertical alignment
    }

    // Convert in degree
    angle = angle * 180.0 / M_PI;
    return -angle;
}

SDL_Surface* rotation3(SDL_Surface *image, double angle) {
    if (!image) 
	{
        fprintf(stderr, "Invalid input image.\n");
        return NULL;
    }

    SDL_LockSurface(image); // Lock the surface to directly access the pixel data

    // Get the image dimensions
    int width = image->w; // Get the width in pixels
    int height = image->h; // Get the height in pixels
    int bpp = image->format->BytesPerPixel;
    int p = image->pitch;
    Uint8* pixels = (Uint8*)image->pixels; // Pointer to the pixel data

    double angle_radian = angle * M_PI / 180.0; // Convert the angle from degrees to radians

    double cos_angle = cos(angle_radian);
    double sin_angle = sin(angle_radian);

    // Calculate the size of the new image after rotation
    int new_w = (int)(fabs(width * cos_angle) + fabs(height * sin_angle));
    int new_h = (int)(fabs(width * sin_angle) + fabs(height * cos_angle));

    // Check that new dimensions are valid
    if (new_w <= 0 || new_h <= 0) 
	{
        fprintf(stderr, "Invalid dimensions for rotated image: new_w=%d, new_h=%d\n", new_w, new_h);
        SDL_UnlockSurface(image); // Unlock the surface before returning
        return NULL;
    }

    // Create a new surface for the rotated image
    SDL_Surface* rotated_image = SDL_CreateRGBSurfaceWithFormat(0, new_w, new_h, 24, image->format->format);
    if (!rotated_image) 
	{
        fprintf(stderr, "SDL_CreateRGBSurfaceWithFormat failed: %s\n", SDL_GetError());
        SDL_UnlockSurface(image); // Unlock the surface before returning
        return NULL;
    }

    Uint8* rotated_pixels = (Uint8*)rotated_image->pixels;

    // Fill the entire surface with white (RGB: 255, 255, 255)
    SDL_FillRect(rotated_image, NULL, SDL_MapRGB(rotated_image->format, 255, 255, 255));

    int center_x = width / 2; // Center of the original image
    int center_y = height / 2;
    int new_center_x = new_w / 2; // Center of the rotated image
    int new_center_y = new_h / 2;

    // Loop over every pixel of the original image
    for (int y = 0; y < new_h; y++) 
	{
        for (int x = 0; x < new_w; x++) 
		{
            // Coordinates of the pixel in the original image after rotation
            int old_x = (int)((x - new_center_x) * cos_angle + (y - new_center_y) * sin_angle) + center_x;
            int old_y = (int)(-(x - new_center_x) * sin_angle + (y - new_center_y) * cos_angle) + center_y;

            // Make sure the new coordinates are within bounds
            if (old_x >= 0 && old_x < width && old_y >= 0 && old_y < height) 
			{
                // Pointer to the pixel in the original image and in the rotated image
                Uint8* original_pixel = pixels + (old_y * p) + (old_x * bpp);
                Uint8* rotated_pixel = rotated_pixels + (y * rotated_image->pitch) + (x * rotated_image->format->BytesPerPixel);

                // Set the pixel color
                rotated_pixel[0] = original_pixel[0];
                rotated_pixel[1] = original_pixel[1];
                rotated_pixel[2] = original_pixel[2];
            }
        }
    }

    SDL_UnlockSurface(image); // Unlock when finished
    SDL_FreeSurface(image);  // Free the original surface if it's no longer needed

    return rotated_image;
}

void rotation_auto(SDL_Surface* surface, Shape* shape, SDL_Renderer* renderer) {
    double angle = calculateOrientation(shape);
    printf("Angle calculé: %f\n", -angle);

    SDL_Surface* rotated_image = rotation3(surface, angle);

    if (rotated_image) 
    {
        printf("Rotation réussie.\n");

        // Create a texture from the rotated image
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, rotated_image);
        if (texture == NULL) 
        {
            printf("Erreur de création de texture: %s\n", SDL_GetError());
        } 
        else 
        {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);

            SDL_Delay(3000);  // Wait 3 seconds 
        }

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(rotated_image);
    } 
    else 
    {
        printf("Erreur de rotation.\n");
    }

    SDL_FreeSurface(surface);
}

int main() {
    // Initialize SDL and SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) == 0) 
    {
        fprintf(stderr, "Erreur d'initialisation : %s\n", SDL_GetError());
        return 1;
    }

    // Creation the window and the renderer
    SDL_Window* window = SDL_CreateWindow("Rotation Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) 
    {
        fprintf(stderr, "Erreur de création SDL : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Put an image and initialize a Shape
    SDL_Surface* surface = IMG_Load("n.png");
    if (!surface) 
    {
        fprintf(stderr, "Erreur de chargement de l'image : %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Shape* shape = CreateShape(1, surface->w / 2, surface->h / 2);
    shape->w = surface->w;
    shape->h = surface->h;

    // Make the automatic rotation
    rotation_auto(surface, shape, renderer);

    free(shape);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
