#include <SDL2/SDL.h>
#include <stdio.h>

// Fonction pour obtenir la couleur d'un pixel
Uint32 get_pixel(SDL_Surface *surface, int x, int y) {
    Uint8 *pixel_ptr = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    Uint32 pixel_color = 0;

    switch (surface->format->BytesPerPixel) {
        case 1:
            pixel_color = *pixel_ptr;
            break;
        case 2:
            pixel_color = *(Uint16 *)pixel_ptr;
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                pixel_color = pixel_ptr[0] << 16 | pixel_ptr[1] << 8 | pixel_ptr[2];
            else
                pixel_color = pixel_ptr[0] | pixel_ptr[1] << 8 | pixel_ptr[2] << 16;
            break;
        case 4:
            pixel_color = *(Uint32 *)pixel_ptr;
            break;
    }
    return pixel_color;
}

// Fonction pour définir la couleur d'un pixel
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    Uint8 *pixel_ptr = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    switch (surface->format->BytesPerPixel) {
        case 1:
            *pixel_ptr = color;
            break;
        case 2:
            *(Uint16 *)pixel_ptr = color;
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                pixel_ptr[0] = (color >> 16) & 0xff;
                pixel_ptr[1] = (color >> 8) & 0xff;
                pixel_ptr[2] = color & 0xff;
            } else {
                pixel_ptr[0] = color & 0xff;
                pixel_ptr[1] = (color >> 8) & 0xff;
                pixel_ptr[2] = (color >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)pixel_ptr = color;
            break;
    }
}

void apply_grayscale(SDL_Surface *surface) {
    for (int y = 0; y < surface->h; y++) {
        for (int x = 0; x < surface->w; x++) {
            Uint32 pixel = get_pixel(surface, x, y);

            // Extraire les composantes RGB du pixel
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            // Calculer la valeur en niveaux de gris
            Uint8 grayscale = (Uint8)(0.3 * r + 0.59 * g + 0.11 * b);

            // Créer une nouvelle couleur en niveaux de gris
            Uint32 new_pixel = SDL_MapRGB(surface->format, grayscale, grayscale, grayscale);

            // Modifier le pixel
            set_pixel(surface, x, y, new_pixel);
        }
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Charger l'image BMP
    SDL_Surface *image = SDL_LoadBMP(argv[1]);
    if (!image) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Verrouiller la surface si nécessaire
    if (SDL_MUSTLOCK(image)) {
        SDL_LockSurface(image);
    }
    apply_grayscale(image);
    // Boucle pour modifier chaque pixel (par exemple, inverser les couleurs)
    for (int y = 0; y < image->h; y++) {
        for (int x = 0; x < image->w; x++) {
            Uint32 pixel_color = get_pixel(image, x, y);

            // Inverser les couleurs (simple exemple)
            Uint8 r, g, b;
            SDL_GetRGB(pixel_color, image->format, &r, &g, &b);
            Uint32 new_color = SDL_MapRGB(image->format, 255 - r, 255 - g, 255 - b);

            set_pixel(image, x, y, new_color);
        }
    }

    // Déverrouiller la surface si nécessaire
    if (SDL_MUSTLOCK(image)) {
        SDL_UnlockSurface(image);
    }

    // Sauvegarder l'image modifiée
    SDL_SaveBMP(image, "image_modified.bmp");

    SDL_FreeSurface(image);
    SDL_Quit();
    return 0;
}
