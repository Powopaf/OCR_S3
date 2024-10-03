#include "grid.h"
#include "Shape/shape.h"
#include "Lib/Lib.h"
#include "../Utils/sdl_utils.h"
#include "List/Node.h"
#include <stdio.h>
#include <stdlib.h>

void ProcessGrid(SDL_Surface *surface) {
    int width = surface->w;
    int height = surface->h;
    int** Map;
    int** surf;
    
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
}

