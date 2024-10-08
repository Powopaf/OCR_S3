#include "grid.h"
#include "Shape/shape.h"
#include "Lib/Lib.h"
#include "../Utils/sdl_utils.h"
#include "List/Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void FindCluster(Node** visited, Node** cluster, Node** shapeList, Shape* shape)
{   
    //printf("Processing Shape %i\n",shape->id);
    if(!ContainsNode(*visited,shape))
    {
        //printf("Pass the contains\n");
        Node* nv = NewNode(shape);
        Node* nc = NewNode(shape);
        AddNode(visited,nv);
        //PrintNodeList(*visited," Visited");
        AddNode(cluster,nc);
        //PrintNodeList(*cluster," Cluster");
        //printf("PreVerif Node %i\n",shape->id);
        Node* current = *shapeList;
        while(current!=NULL)
        {
            //printf("Verif Node %i\n",current->data->id);
            if(shape->id!=current->data->id)
            {
                int seuil = 100;
                if(distance(shape,current->data)<shape->AverageDist)
                {
                    FindCluster(visited,cluster,shapeList,current->data);
                }
            }
            current = current->next;
        }
    }
    else
    {
        //printf("Node %i already Visited\n",shape->id);
    }

}

void AverageDist(Node* shapeList,Shape* s)
{   
    double sum = 0;
    int count = 0;
    Node* current = shapeList;
    while(current->next!=NULL)
    {
        if(s->id!=current->data->id)
        {
            sum+=distance(s,current->data);  
            count++;
        }
        current = current->next;
    }
    s->AverageDist = sum/(double)count;
}

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
            h < 0.0 * averageH ||
            w > 3 * averageW ||
            w < 0.0 * averageW ||
            l > 3 * averageL ||
            l < 0.0 * averageL)
        {
            RemoveNode(shapeList, i);
        }
        else
        {
            i++;
        }
        current = next;
    }
    current = *shapeList;
    while(current != NULL)
    {
        AverageDist(*shapeList,current->data);
        //printf("AvDist: %f\n",current->data->AverageDist);
        current = current->next;
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
                ComputeCenter(s);

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
    
    Node* c = shapeList;
    Node* visited = NULL;
    int i = 0;
    while(c!=NULL)
    {
        Node* cluster = NULL;
        FindCluster(&visited,&cluster,&shapeList,c->data);
        Draw(surface,cluster,(i/14)*14,i,(255-i)/2);
        //PrintNodeList(cluster," Cluster");
        FreeNodeList(&cluster,0);
        i = (i + 50)%255;
        c = c->next;
    }
    FreeNodeList(&visited,0);

    //Draw(surface, shapeList,255,255,0);

    FreeNodeList(&shapeList,1);

    SDL_UnlockSurface(surface);
}

