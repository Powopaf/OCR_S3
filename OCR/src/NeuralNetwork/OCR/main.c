#include "../NeuralNetwork.h"

int main(int argc, char** argv)
{
    
    if(1)
    {
        SDL_Surface* surface = SDL_LoadBMP(argv[1]);
        char letter = LetterRecognition(surface);
        SDL_FreeSurface(surface);
        printf("Letter: %c\n", letter);
        return 0;
    }
}
