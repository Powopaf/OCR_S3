#include "Lib.h"
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>

SDL_Surface* DuplicateSurface(SDL_Surface* surface)
{
    SDL_UnlockSurface(surface);
    SDL_Surface* duplicate_surface = SDL_CreateRGBSurfaceWithFormat(0, surface->w, surface->h, 24, SDL_PIXELFORMAT_RGB24);
    if(duplicate_surface==NULL)
    {
        err(1,"ERROR: duplicate surface\n");
    }

    if(SDL_BlitSurface(surface, NULL, duplicate_surface, NULL) < 0) 
    {
        SDL_FreeSurface(duplicate_surface); // Free the duplicate in case of an error
        err(1,"ERROR: copy duplicate surface\n");
    }
    SDL_LockSurface(surface);
    return duplicate_surface;
}


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

int IsOnSurface(int j, int i, int h, int w)
{
    return (j >= 0 && j < h && i >= 0 && i < w);
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

double distance(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

int ListSum(Node* lst)
{
    int sum = 0;
    while(lst!=NULL)
    {
        sum+=lst->data->Len;
        lst = lst->next;
    }
    return sum;
}

Node** ReduceArray(Node** lst, int* size, int nsize)
{
    int count = nsize;
    if(nsize==0)
    {
        for(int i = 0; i<*size; i++)
        {
            if(lst[i]!=NULL)
            {
                count++;
            }
        }
    }

    
    Node** res = (Node**)malloc(count*sizeof(Node*));
    int k = 0;
    for(int i = 0; i<*size; i++)
    {
        if(lst[i]!=NULL)
        {
            res[k] = lst[i];
            k++;
        }
    }
    *size = count;
    free(lst);
    return res;
}

void FindShapePosMatrix(Node* shapeList, int* j, int* i)
{
    // find for each Shape the position in the matrix, store the result in
    // Shape->Matj and Shape->Mati, and store the dimension of the matrix in j
    // and i
    return;
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
        for (int j = s->Minj; j <= s->Maxj; j++) 
        {
            Uint8* pixel1 = pix + j * p + s->Maxi * bpp; 
            Uint8* pixel2 = pix + j * p + s->Mini * bpp; 
            pixel1[0] = pixel2[0] = r;
            pixel1[1] = pixel2[1] = g;
            pixel1[2] = pixel2[2] = b;
        }

        // Draw horizontal lines
        for (int i = s->Mini; i <= s->Maxi; i++)
        {
            Uint8* pixel1 = pix + s->Maxj * p + i * bpp; 
            Uint8* pixel2 = pix + s->Minj * p + i * bpp; 
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

void DrawList(SDL_Surface* surface, Node** clusterList, int size)
{
    for(int i = 0; i<size; i++)
    {
        float hue = (i * 360.0 / size);
        int r = (int)(255 * (1 + sin(hue * 3.14 / 180)) / 2);
        int g = (int)(255 * (1 + sin((hue + 120) * 3.14 / 180)) / 2);
        int b = (int)(255 * (1 + sin((hue + 240) * 3.14 / 180)) / 2);
        Draw(surface,clusterList[i],r,g,b);
    }
}
