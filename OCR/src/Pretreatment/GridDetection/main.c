#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "grid.h"
#include "../Utils/sdl_utils.h"
#include "Shape/shape.h"
#include "List/Node.h"
int main()
{
    for (int i = 1; i < 7; i++)
    {
        printf("Processing image %i...\n", i);
        char* s = NULL;
        asprintf(&s, "img/img%i.bmp", i);
        char *sg = NULL;
        asprintf(&sg, "img/imgGrid%i.bmp", i);
        sdl_setup();
        SDL_Surface* surface = SDL_LoadBMP(s);
        if (surface == NULL)
        {
            err(1, "Unable to load image: %s\n", SDL_GetError());
        }
        /*test
        Node* lst = NULL;
        Shape* s1 = CreateShape(1,0,0);
        Shape* s2 = CreateShape(2,3,2);
        Shape* s3 = CreateShape(3,4,4);
        Node* c = NewNode(s1);
        Node* c2 = NewNode(s2);
        Node* c3 = NewNode(s3);
        AddNode(&lst,c);
        AddNode(&lst,c2);
        AddNode(&lst,c3);
        printf("bool: %i\n",ContainsNode(lst,s2));
        */
        ProcessGrid(surface);
        SDL_SaveBMP(surface, sg);
        SDL_FreeSurface(surface);
        SDL_Quit();
        free(s);
        free(sg);
    }
    return 0;
}
