#include "Lib.h"
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>


void MallocMatrix(int ***arr, int sizex, int sizey) {
    *arr = (int **)malloc(sizex * sizeof(int *));
    if (*arr == NULL) {
        err(1, "Memory allocation error\n");
    }

    for (int i = 0; i < sizex; i++) {
        (*arr)[i] = (int *)malloc(sizey * sizeof(int));
        if ((*arr)[i] == NULL) {
            err(1, "Memory allocation error for row %i", i);
        }
    }
}

void FreeMatrix(int **arr, int sizex) {
    for (int i = 0; i < sizex; i++) {
        free(arr[i]);  // Free each row
    }
    free(arr);  // Free the array of pointers
}

int IsOnSurface(int x, int y, int h, int w)
{
    return (x >= 0 && x < h && y >= 0 && y < w);
}

void InitMatrix(SDL_Surface *surface, int*** Map, int*** surf)
{
    SDL_PixelFormat* format = surface->format;
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            (*Map)[j][i] = 0;
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Uint8* pixel = pix + j * p + i * bpp;
            (*surf)[j][i] = pixel[0];
        }
    }
}

void PrintNodeList(Node* lst, char* name)
{
    printf("%s:",name);
    Node* c = lst;
    while(c!=NULL)
    {
        printf(" %i",c->data->id);
        c = c->next;
    }
    printf("\n");

}

double distance(Shape* s1, Shape* s2)
{
    double dx = s2->Cx - s1->Cx;
    double dy = s2->Cy - s1->Cy;
    double distance = sqrt(dx * dx + dy * dy);
    // Ponderer la distance selon la taille des formes
    double sizeFactor = (s1->Len + s2->Len) / 2.0;
    return distance / sizeFactor;  // distance ajustée
    /*
    double dx = s2->Cx - s1->Cx;
    double dy = s2->Cy - s1->Cy;
    return sqrt(dx * dx + dy * dy);
    */
}

void Draw(SDL_Surface *surface, Node* shape_lst, int r, int g, int b)
{
    SDL_PixelFormat* format = surface->format;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_LockSurface(surface);
   
    
    Node* n = shape_lst;
    while(n!=NULL)
    {
        Shape* s = n->data;
        // Draw vertical lines
        for (int j = s->MinX; j <= s->MaxX; j++) 
        {
            Uint8* pixel1 = pix + j * p + s->MaxY * bpp; 
            Uint8* pixel2 = pix + j * p + s->MinY * bpp; 
            pixel1[0] = pixel2[0] = r;
            pixel1[1] = pixel2[1] = g;
            pixel1[2] = pixel2[2] = b;
        }

        // Draw horizontal lines
        for (int i = s->MinY; i <= s->MaxY; i++)
        {
            Uint8* pixel1 = pix + s->MaxX * p + i * bpp; 
            Uint8* pixel2 = pix + s->MinX * p + i * bpp; 
            pixel1[0] = pixel2[0] = r;
            pixel1[1] = pixel2[1] = g;
            pixel1[2] = pixel2[2] = b;
        }

        n = n->next;
        Uint8* px = pix + s->Cx * p + s->Cy * bpp;
        px[0] = r;
        px[0] = g;
        px[2] = b;
    }
    SDL_UnlockSurface(surface);
}

