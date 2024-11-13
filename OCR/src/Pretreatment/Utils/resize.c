#include "resize.h"

SDL_Surface* resize_surface(SDL_Surface* original_surface) {
    if (!original_surface) {
        SDL_Log("Surface originale non valide : %s", SDL_GetError());
        return NULL;
    }

    int target_height = 28;
    int target_width = 28;
    int original_width = original_surface->w;
    int original_height = original_surface->h;

    // Calcul de la nouvelle largeur en conservant le ratio
    int new_width = (original_width * target_height) / original_height;

    // Redimensionner l'image à une hauteur de 28 pixels, largeur ajustée
    SDL_Surface* resized_surface = SDL_CreateRGBSurfaceWithFormat(0, new_width, target_height,
                                                                  original_surface->format->BitsPerPixel,
                                                                  original_surface->format->format);
    if (!resized_surface) {
        SDL_Log("Erreur lors de la création de la surface redimensionnée : %s", SDL_GetError());
        return NULL;
    }

    // Redimensionner l'image en hauteur de 28 pixels
    if (SDL_BlitScaled(original_surface, NULL, resized_surface, NULL) < 0) {
        SDL_Log("Erreur lors du redimensionnement de la surface : %s", SDL_GetError());
        SDL_FreeSurface(resized_surface);
        return NULL;
    }

    // Créer une surface finale de 28x28 pixels avec un fond noir
    SDL_Surface* final_surface = SDL_CreateRGBSurfaceWithFormat(0, target_width, target_height,
                                                                original_surface->format->BitsPerPixel,
                                                                original_surface->format->format);
    if (!final_surface) {
        SDL_Log("Erreur lors de la création de la surface finale : %s", SDL_GetError());
        SDL_FreeSurface(resized_surface);
        return NULL;
    }

    // Remplir la surface finale avec du noir
    SDL_FillRect(final_surface, NULL, SDL_MapRGB(final_surface->format, 0, 0, 0));

    // Si la nouvelle largeur est supérieure à 28 pixels, on la redimensionne à 28 pixels
    SDL_Rect dest_rect;
    if (new_width > target_width) {
        SDL_Surface* scaled_surface = SDL_CreateRGBSurfaceWithFormat(0, target_width, target_height,
                                                                     original_surface->format->BitsPerPixel,
                                                                     original_surface->format->format);
        if (!scaled_surface) {
            SDL_Log("Erreur lors de la création de la surface redimensionnée à 28x28 : %s", SDL_GetError());
            SDL_FreeSurface(resized_surface);
            SDL_FreeSurface(final_surface);
            return NULL;
        }

        if (SDL_BlitScaled(resized_surface, NULL, scaled_surface, NULL) < 0) {
            SDL_Log("Erreur lors du redimensionnement final : %s", SDL_GetError());
            SDL_FreeSurface(scaled_surface);
            SDL_FreeSurface(resized_surface);
            SDL_FreeSurface(final_surface);
            return NULL;
        }

        SDL_FreeSurface(resized_surface);
        resized_surface = scaled_surface;
        new_width = target_width;
    }

    // Centrer l'image redimensionnée sur la surface finale de 28x28 pixels
    dest_rect.x = (target_width - new_width) / 2;
    dest_rect.y = 0;
    dest_rect.w = new_width;
    dest_rect.h = target_height;

    SDL_BlitSurface(resized_surface, NULL, final_surface, &dest_rect);

    // Libérer la surface redimensionnée temporaire
    SDL_FreeSurface(resized_surface);

    return final_surface;
}
