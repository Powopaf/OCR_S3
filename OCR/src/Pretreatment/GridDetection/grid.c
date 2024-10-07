#include "grid.h"
#include "Shape/shape.h"
#include "Lib/Lib.h"
#include "../Utils/sdl_utils.h"
#include "List/Node.h"
#include <stdio.h>
#include <stdlib.h>

void ShapeFilter(Node** shapeList)
{
    Node* current = *shapeList;
    int sumH = 0;
    int sumW = 0;
    int sumL = 0;
    int count = 0;
    while (current != NULL)
    {
        sumH += current->data->MaxY - current->data->MinY;
        sumW += current->data->MaxX - current->data->MinX;
        sumL += current->data->Len;
        count++;
        current = current->next;
    }

    double averageH = (double)sumH / count;
    double averageW = (double)sumW / count;
    double averageL = (double)sumL / count;


    current = *shapeList;
    int i = 0;
    
    while (current != NULL)
    {
        Node* next = current->next;
        int h = current->data->MaxY - current->data->MinY;
        int w = current->data->MaxX - current->data->MinX;
        int l = current->data->Len;
        if (h > 3 * averageH ||
            h < 0.2 * averageH ||
            w > 3 * averageW ||
            w < 0.2 * averageW ||
            l > 2 * averageL ||
            l < 0.2 * averageL)
        {
            RemoveNode(shapeList, i);
        }
        else
        {
            i++;
        }
        current = next;
    }
}

void ProcessGrid(SDL_Surface *surface) {
    int width = surface->w;
    int height = surface->h;
    int** Map;
    int** surf;
    
    SDL_LockSurface(surface);

    MallocMatrix(&Map, height, width);
    MallocMatrix(&surf, height, width);
    
    InitMatrix(surface,&Map,&surf);

    Node* shapeList = NULL;
    int id = 0;

    for(int j = 0; j < height; j++) 
    {
        for(int i = 0; i < width; i++) 
        {
            if (surf[j][i] == 255 && Map[j][i] == 0) {
                id++;
                Shape* s = CreateShape(id, j, i);
                FindShape(s, surf, Map, j, i, height, width);

                if (IsShapeValid(surface, s)) 
                {
                    Node* n = NewNode(s);
                    AddNode(&shapeList, n);
                } 
                else 
                {
                    free(s);
                }
            }
        }
    }

    FreeMatrix(Map, height);
    FreeMatrix(surf, height);

    ShapeFilter(&shapeList);

    Draw(surface, shapeList);

    FreeNodeList(&shapeList);

    SDL_UnlockSurface(surface);
}

