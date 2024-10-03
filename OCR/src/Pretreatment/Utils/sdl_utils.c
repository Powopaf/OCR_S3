#include <SDL2/SDL.h>
#include <err.h>

void sdl_setup() {
    // we can add arguements if needed
    if(SDL_Init(SDL_INIT_VIDEO)) {
        char* arg[3] = { "../../Bash/rmAllBMP.sh", "4", NULL };
        execvp("../../Bash/rmAllBMP.sh, arg");
        errx(EXIT_FAILURE, "fail to init sdl_video: %s", SDL_GetError());
    }
}

void sdl_close() {
    // we can add arguements if needed
    SDL_Quit();
}
/*
void drawline(SDL_Renderer *renderer, 
        int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b) {
    
     // x1,y1,x2,y2 -> coordinate to draw between
     // r,g,b -> the color of the line
     
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}*/
