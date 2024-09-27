#include <SDL2/SDL.h>
#include <err.h>

#include "Shape.h"
#include "../Utils/sdl_utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Draw(SDL_Surface *surface, Shape* s)
{
    SDL_PixelFormat* format = surface->format;
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_LockSurface(surface);
    
    for(int j = s->MinX; j <= s->MaxX; j++) 
    {
        Uint8* pixel1 = pix + j * p + s->MaxY * bpp; // magic line
        Uint8* pixel2 = pix + j * p + s->MinY * bpp; // magic line
        pixel1[0] = 127;
        pixel1[1] = 127;
        pixel1[2] = 127;

        pixel2[0] = 127;
        pixel2[1] = 127;
        pixel2[2] = 127;
    }
    for(int i = s->MinY; i<= s->MaxY; i++)
    {
        Uint8* pixel1 = pix + s->MaxX * p + i * bpp; // magic line
        Uint8* pixel2 = pix + s->MinX * p + i * bpp; // magic line
        pixel1[0] = 127;
        pixel1[1] = 127;
        pixel1[2] = 127;


        pixel2[0] = 127;
        pixel2[1] = 127;
        pixel2[2] = 127;

    }
    
    SDL_UnlockSurface(surface);
}

void MallocMatrix(int ***arr, int sizex, int sizey)
{
	*arr = (int **)malloc(sizex * sizeof(int *));
	
	if (*arr == NULL) 
	{
        err(1,"Erreur d'allocation de mémoire\n");
    }

	for(int i = 0; i<sizex; i++)
	{
		(*arr)[i] = (int *)malloc(sizey * sizeof(int));
		if((*arr)[i] == NULL)
		{
			err(1,"Erreur d'allocation de mémoire pour la ligne %i",i);
		}
	}
}

void FindShape( Shape* s, int** surface, int** Map, int x, int y)
{
    Map[x][y] = s->id;
    s->Len++;
    if(s->MaxX<x)
    {
        s->MaxX = x;
    }
    if(s->MinX>x)
    {
        s->MinX = x;
    }
    if(s->MaxY<y)
    {
        s->MaxY = y;
    }
    if(s->MinY>y)
    {
        s->MinY = y;
    }

    if(Map[x+1][y]==0 && surface[x+1][y]==255)
    {
        FindShape(s,surface,Map,x+1,y);
    }
    if(Map[x-1][y]==0 && surface[x-1][y]==255)
    {
        FindShape(s,surface,Map,x-1,y);
    }
    if(Map[x][y+1]==0 && surface[x][y+1]==255)
    {
        FindShape(s,surface,Map,x,y+1);
    }
    if(Map[x][y-1]==0 && surface[x][y-1]==255)
    {
        FindShape(s,surface,Map,x,y-1);
    }
}

void Grid(SDL_Surface *surface) {
    SDL_PixelFormat* format = surface->format;
    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels;
    SDL_LockSurface(surface);
    
    int id = 0;
    
    int size = width*height;
    Shape* shapes = malloc(size * sizeof(Shape));
    //Shape ShapeList[height*width];

    int** Map;
    MallocMatrix(&Map,height,width);
    for(int j = 0; j<height; j++)
    {
        for(int i = 0; i<width; i++)
        {
            Map[j][i] = 0;
        }
    }
    int** surf;
    MallocMatrix(&surf,height,width);
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8* pixel = pix + j * p + i * bpp; // magic line
            surf[j][i] = pixel[0];
        }
    }
    int n = 0;
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8* pixel = pix + j * p + i * bpp; // magic line
            Uint8 color = pixel[0];
            if(color==255 && Map[j][i]==0)
            {
                id++;
                Shape s;
                s.id = id;
                s.Cx = j;
                s.Cy = i;
                s.MaxX = j;
                s.MaxY = i;
                s.MinX = j;
                s.MinY = i;
                FindShape(&s,surf,Map,j,i);
                shapes[s.id-1] = s;
            }
        }
    }
    
    for(int j = 0; j < id; j++) 
    {
        Draw(surface,&shapes[j]);
    }
    /*
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8* pixel = pix + j * p + i * bpp; // magic line
            if(Map[j][i]!=0)
            {
                if(Map[j][i]%2==0)
                {
                    pixel[0] = 127;
                }
                else
                {
                    pixel[2] = 127;
                }
            }
        }
    }    
    */
    
    //printf("%i\n",s.Cx);
    //printf("%i\n",s.Cy);
    //printf("%i\n",s.Len);
    SDL_UnlockSurface(surface);
}
int main(int argc, char* argv[]) {

    sdl_setup();
    SDL_Surface* surface = SDL_LoadBMP("img.bmp"); //convert() create a img.bmp
    Grid(surface);
    SDL_SaveBMP(surface, "imgGrid.bmp");
    SDL_FreeSurface(surface);
    sdl_close();
}
