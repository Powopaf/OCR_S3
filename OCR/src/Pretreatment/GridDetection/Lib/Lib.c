#include "Lib.h"
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>

// Function to create a duplicate of an SDL_Surface
SDL_Surface* DuplicateSurface(SDL_Surface* surface)
{
    SDL_UnlockSurface(surface); // Unlock the surface for safe manipulation
    SDL_Surface* duplicate_surface = SDL_CreateRGBSurfaceWithFormat(0, surface->w, surface->h, 24, SDL_PIXELFORMAT_RGB24);
    if(duplicate_surface == NULL)
    {
        err(1,"ERROR: duplicate surface\n"); // Handle allocation failure
    }

    if(SDL_BlitSurface(surface, NULL, duplicate_surface, NULL) < 0) 
    {
        SDL_FreeSurface(duplicate_surface); // Free the duplicate in case of an error
        err(1,"ERROR: copy duplicate surface\n"); // Handle blit failure
    }
    SDL_LockSurface(surface); // Lock the original surface again
    return duplicate_surface; // Return the duplicated surface
}

// Function to allocate a 2D dynamic integer matrix
void GMallocMatrix(int ***arr, int sizex, int sizey) {
    *arr = (int **)malloc(sizex * sizeof(int *));
    if (*arr == NULL) {
        err(1, "Memory allocation error\n"); // Handle allocation failure
    }

    for (int i = 0; i < sizex; i++) {
        (*arr)[i] = (int *)malloc(sizey * sizeof(int));
        if ((*arr)[i] == NULL) {
            err(1, "Memory allocation error for row %i", i); // Handle row allocation failure
        }
    }
}

// Function to free a dynamically allocated 2D integer matrix
void GFreeMatrix(int **arr, int sizex) {
    for (int i = 0; i < sizex; i++) {
        free(arr[i]);  // Free each row
    }
    free(arr);  // Free the array of pointers
}

// Function to check if a given point (j, i) is within the bounds of a surface
int IsOnSurface(int j, int i, int h, int w)
{
    return (j >= 0 && j < h && i >= 0 && i < w); // Return true if within bounds
}

// Function to initialize a 2D matrix and populate it with pixel data from an SDL_Surface
void InitMatrix(SDL_Surface *surface, int*** Map, int*** surf)
{
    SDL_PixelFormat* format = surface->format; // Get pixel format
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels; // Get pixel data

    // Initialize Map with zeros
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            (*Map)[j][i] = 0; // Set all values to 0
        }
    }

    // Populate surf with pixel values
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Uint8* pixel = pix + j * p + i * bpp; // Calculate pixel position
            (*surf)[j][i] = pixel[0]; // Store pixel value (0 or 1)
        }
    }
}

// Function to print the IDs of nodes in a linked list
void PrintNodeList(Node* lst, char* name)
{
    printf("%s:", name);
    Node* c = lst;
    while(c != NULL)
    {
        printf(" %i", c->data->id); // Print each node's ID
        c = c->next;
    }
    printf("\n");
}

// Function to calculate the distance between two points (x1, y1) and (x2, y2)
double distance(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy); // Return Euclidean distance
}

// Function to calculate the sum of lengths from a linked list of nodes
int ListSum(Node* lst)
{
    int sum = 0;
    while(lst != NULL)
    {
        sum += lst->data->Len; // Add each node's length to sum
        lst = lst->next;
    }
    return sum; // Return the total sum
}

// Function to reduce an array of nodes by removing NULL elements
Node** ReduceArray(Node** lst, int* size, int nsize)
{
    int count = nsize; // Initialize count to the new size
    if(nsize == 0) // If no new size is given, count non-NULL nodes
    {
        for(int i = 0; i < *size; i++)
        {
            if(lst[i] != NULL)
            {
                count++;
            }
        }
    }

    Node** res = (Node**)malloc(count * sizeof(Node*)); // Allocate new array
    int k = 0;
    for(int i = 0; i < *size; i++)
    {
        if(lst[i] != NULL) // Copy non-NULL nodes to new array
        {
            res[k] = lst[i];
            k++;
        }
    }
    *size = count; // Update the size pointer
    free(lst); // Free the old list
    return res; // Return the new list
}

void getRandomColor(int* r, int* g, int* b, int id, int nbOfColor)
{
    float hue = (id * 360.0 / ((nbOfColor+5)/2.0)); // Calculate hue for color
    *r = (int)(255 * (1 + sin(hue * 3.14 / 180)) / 2); // RGB values based on hue
    *g = (int)(255 * (1 + sin((hue + 120) * 3.14 / 180)) / 2);
    *b = (int)(255 * (1 + sin((hue + 240) * 3.14 / 180)) / 2);
}

void DrawLine(SDL_Surface *surface, Shape *shape1, Shape *shape2, int r, int g, int b)
{
    SDL_PixelFormat* format = surface->format;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;

    int x1 = (shape1->Mini + shape1->Maxi) / 2;
    int y1 = (shape1->Minj + shape1->Maxj) / 2;
    int x2 = (shape2->Mini + shape2->Maxi) / 2;
    int y2 = (shape2->Minj + shape2->Maxj) / 2;

    // Bresenham's line algorithm
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;
    int i = 0;
    while (1) {

        Uint8* pixel = pix + y1 * p + x1 * bpp;
        pixel[0] = r;
        pixel[1] = g;
        pixel[2] = b;

        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
        i++;
    }
    /*
    for(int i = y1-2; i<y1+2; i++)
    {
        for(int j = x1-2; j<x1+2; j++)
        {
            Uint8* pixel = pix + i * p + j * bpp;
            pixel[0] = 0;
            pixel[1] = 255;
            pixel[2] = 0;
        }
    }
    */
}

// Function to draw shapes on an SDL_Surface based on a linked list
void Draw(SDL_Surface *surface, Node* shape_lst, int r, int g, int b, int DrawConnection)
{
    SDL_PixelFormat* format = surface->format;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels; // Get pixel data
    SDL_LockSurface(surface); // Lock the surface for safe manipulation
    Node* prev = NULL;
    Node* n = shape_lst;
    while(n != NULL)
    {   
        if(prev!=NULL && DrawConnection==1)
        {
             // Draw a line between shapes
             DrawLine(surface, prev->data, n->data, r, g, b);
        }
        prev = n;
        Shape* s = n->data;
        // Draw vertical lines
        for (int j = s->Minj; j <= s->Maxj; j++) 
        {
            Uint8* pixel1 = pix + j * p + s->Maxi * bpp; 
            Uint8* pixel2 = pix + j * p + s->Mini * bpp; 
            pixel1[0] = pixel2[0] = r; // Set pixel color
            pixel1[1] = pixel2[1] = g;
            pixel1[2] = pixel2[2] = b;
        }

        // Draw horizontal lines
        for (int i = s->Mini; i <= s->Maxi; i++)
        {
            Uint8* pixel1 = pix + s->Maxj * p + i * bpp; 
            Uint8* pixel2 = pix + s->Minj * p + i * bpp; 
            pixel1[0] = pixel2[0] = r; // Set pixel color
            pixel1[1] = pixel2[1] = g;
            pixel1[2] = pixel2[2] = b;
        }

        n = n->next; // Move to the next node
        Uint8* px = pix + s->Cx * p + s->Cy * bpp; // Set center pixel
        px[0] = r;
        px[1] = g;
        px[2] = b;
    }
    SDL_UnlockSurface(surface); // Unlock the surface after drawing
}

// Function to draw a list of clusters on an SDL_Surface with unique colors
void DrawList(SDL_Surface* surface, Node** clusterList, int size)
{
    Draw(surface, clusterList[0], 255, 0, 0,0); 
    printf("size %i\n",size);
    for(int i = 1; i < size; i++)
    {
        int r,g,b;
        getRandomColor(&r, &g, &b, i, size); // Get a random color for each cluster
        Draw(surface, clusterList[i], r, g, b,0); // Draw each cluster with its color
    
        /*printf("clusterList[i]         %i\n",clusterList[i]!=NULL);
        printf("clusterList[i-1]       %i\n",clusterList[i]!=NULL);
        printf("ClusterList[i]->data   %p\n",clusterList[i]);
        printf("ClusterList[i-1]->data %p\n",clusterList[i-1]);*/
        if (clusterList[i-1] != NULL && clusterList[i] != NULL) {
            DrawLine(surface, clusterList[i-1]->data, clusterList[i]->data, 255, 0, 0);
        }
    }
}

