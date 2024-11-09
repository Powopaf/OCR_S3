#include "../NeuralNetwork.h"

#define nbLetter 3
#define nbImg 10
#define nbPixel 784 //28*28

char*** MallocDataSet()
{
    char*** arr = malloc(nbLetter*sizeof(char**));
    for(int i = 0; i<nbLetter; i++)
    {
        arr[i] = malloc(nbImg*sizeof(char*));
        for(int j = 0; j<nbImg; j++)
        {
            arr[i][j] = NULL;//calloc(nbPixel,sizeof(char));
        }
    }
    return arr;
}

void FreeDataSet(char*** arr)
{
    for(int i = 0; i<nbLetter; i++)
    {
        for(int j = 0; j<nbImg; j++)
        {
            if(arr[i][j]!=NULL)
            {
                free(arr[i][j]);
            }
        }
        free(arr[i]);
    }
    free(arr);
}

char* LoadImgData(SDL_Surface* surface)
{
    char* res = calloc(nbPixel,sizeof(char));
    int k = 0;

    int width = surface->w;
    int height = surface->h;
    int p = surface->pitch;
    int bpp = surface->format->BytesPerPixel;
    Uint8* pix = (Uint8*)surface->pixels; // Get pixel data


    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Uint8* pixel = pix + j * p + i * bpp;
            if(pixel[0]==0)
            {
                res[k] = 1;
            }
            k++;
        }
    }

    return res;
}

char*** LoadDataSet(char*** arr)
{
    for(int l = 0; l<nbLetter;l++)
    {
        for(int i = 0; i<nbImg; i++)
        {
            char* filename = NULL;
            printf("test img : data/%c/%c_%i.bmp\n",(char)(l+65),(char)(l+65),i);
            asprintf(&filename,"data/%c/%c_%i.bmp",(char)(l+65),(char)(l+65),i);
            SDL_Surface* surface = SDL_LoadBMP(filename);
            free(filename);
            arr[l][i] = LoadImgData(surface);
            SDL_FreeSurface(surface);
        }
    }

    return arr;
}