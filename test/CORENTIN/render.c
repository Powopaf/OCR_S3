#include <SDL2/SDL.h>
#include <stdio.h>
#include "neural.h"

void drawPoint(SDL_Renderer *renderer, int x, int y, int size, int Safe) {
    SDL_Rect rect;
    rect.x = x - size / 2; // Centrer le carré sur le point
    rect.y = y - size / 2;
    rect.w = size;
    rect.h = size;

    // Couleur des points (rouge)
	if(Safe==0)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge opaque
	else
		SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // Bleu clair opaque
    SDL_RenderFillRect(renderer, &rect);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur d'initialisation SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Graphique avec SDL2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1000, 1000,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Erreur de création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Couleur de fond
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Dessiner des points
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Couleur des points (bleu)
	init();	
	int pointSize = 10;
	for(int i = 0; i<SampleSize; i++)
	{
		DataPoint p = Sample[i];
		drawPoint(renderer,p.x*100.0,p.y*100.0,pointSize,p.Safe);
	}
	

    SDL_RenderPresent(renderer);

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0; // Fermer la boucle si l'utilisateur ferme la fenêtre
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
