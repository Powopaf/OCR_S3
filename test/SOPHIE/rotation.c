#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wtype-limits"
#define _USE_MATH_DEFINES
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC diagnostic pop

// Fonction pour obtenir un pixel
uint8_t getPixel(SDL_Surface *surface, int x, int y)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) {
        // Renvoie un pixel noir par défaut (0 pour 8 bits, par exemple)
        return 0;
    }

    // Accéder au pixel à la position (x, y)
    uint8_t *pixels = (uint8_t *)((uint8_t *)surface->pixels + y * surface->pitch);
    return pixels[x];
}

// Fonction pour définir un pixel
void putPixel(SDL_Surface *surface, int x, int y, uint8_t pixel)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) {
        return; // Ignorer si hors limites
    }

    // Mettre à jour le pixel à la position (x, y)
    uint8_t *pixels = (uint8_t *)((uint8_t *)surface->pixels + y * surface->pitch);
    pixels[x] = pixel;
}

// Rotation d'une image
SDL_Surface *rotation(SDL_Surface *image, double angle)
{
    // Dimensions de l'image
    int w = image->w;
    int h = image->h;

    // Création d'une nouvelle surface pour l'image tournée, en 8 bits (indexée)
    SDL_Surface *rotated_image = SDL_CreateRGBSurfaceWithFormat(0, w, h, 8, SDL_PIXELFORMAT_INDEX8);
    if (!rotated_image) {
        fprintf(stderr, "Erreur lors de la création de la surface : %s\n", SDL_GetError());
        return NULL;
    }

    // Conversion de l'angle en radians
    double angle_rad = angle * (M_PI / 180);
    int center_x = w / 2;
    int center_y = h / 2;
    double cos_angle = cos(angle_rad);
    double sin_angle = sin(angle_rad);

    // Parcourir chaque pixel de l'image d'origine
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            // Calcul des coordonnées de rotation
            double xOff = x - center_x;
            double yOff = y - center_y;

            int new_x = round(xOff * cos_angle + yOff * sin_angle + center_x);
            int new_y = round(yOff * cos_angle - xOff * sin_angle + center_y);

            // Vérifier que les coordonnées sont dans les limites
            if (new_x >= 0 && new_x < w && new_y >= 0 && new_y < h) {
                uint8_t pixel = getPixel(image, x, y);
                putPixel(rotated_image, new_x, new_y, pixel);
            }
        }
    }
    return rotated_image;
}

// Rotation par cisaillement
SDL_Surface *Rotation_shearing(SDL_Surface *image, double angle)
{
    int w = image->w;
    int h = image->h;

    // Créer une surface pour stocker l'image cisaillée, en 8 bits
    SDL_Surface *rotated_image = SDL_CreateRGBSurfaceWithFormat(0, w, h, 8, SDL_PIXELFORMAT_INDEX8);
    if (!rotated_image) {
        fprintf(stderr, "Erreur lors de la création de la surface : %s\n", SDL_GetError());
        return NULL;
    }

    double angle_rad = angle * (M_PI / 180);
    int center_x = w / 2;
    int center_y = h / 2;
    double sin_angle = sin(angle_rad);
    double tan_angle = tan(angle_rad / 2);

    // Boucle pour chaque pixel
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            double xOff = (x - center_x);
            double yOff = (y - center_y);

            // Cisaillement 1
            int new_x = round(xOff - yOff * tan_angle);
            int new_y = round(yOff);

            // Cisaillement 2
            new_y = round(new_x * sin_angle + new_y);

            // Cisaillement 3
            new_x = round(new_x - new_y * tan_angle);

            new_x += center_x;
            new_y += center_y;

            // Vérification des limites
            if (new_x >= 0 && new_x < w && new_y >= 0 && new_y < h) {
                uint8_t pixel = getPixel(image, x, y);
                putPixel(rotated_image, new_x, new_y, pixel);
            }
        }
    }
    return rotated_image;
}
int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image initialization failed: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Image Rotation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *screen_surface = SDL_GetWindowSurface(window);

    SDL_Surface *image = IMG_Load("n1_1.png");
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
