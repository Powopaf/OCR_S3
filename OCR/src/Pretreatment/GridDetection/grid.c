#include "grid.h"
#include <unistd.h>
#include <math.h>

#define M_PI 3.14159265358979323846

void AverageClusterSize(Node** shapeList, int** visited, int id, double* avHeight, double* avWidth)
{
    /*
    Function to calculate the average height and width of shapes in a cluster
    */
    Node* c = *shapeList;
    int count = 0;
    double sumH = 0;
    double sumW = 0;
    while (c != NULL)
    {
        if((*visited)[c->data->id - 1] == id)
        {
            sumH += c->data->h;
            sumW += c->data->w;
            count++;
        }
        c = c->next;
    }
    *avHeight = sumH / (double)count;
    *avWidth = sumW / (double)count;
}

void AdjustList(Node** lst) 
{
    /*
    Function to adjust the shape list based on average height and a threshold
    */
    if (*lst == NULL) 
    {
        return;
    }

    int sumH = 0;
    Node* c = *lst;
    int count = 0;

    // Calculate the average height of shapes in the list
    while (c != NULL) 
    {
        sumH += c->data->h;
        count++;
        c = c->next;
    }

    double avH = sumH / (double)count;
    Node* prev = NULL;
    c = *lst;
    double threshold = 5.0;

    // go through the list and remove nodes below a height threshold
    while (c != NULL) 
    {
        if (c->data->h < avH - threshold) 
        {
            Node* temp = c;
            if (prev == NULL) 
            {
                *lst = c->next;
            } 
            else 
            {
                prev->next = c->next;
            }
            c = c->next;

            // Free memory correctly
            free(temp); // Free the Node
        } 
        else 
        {
            prev = c;
            c = c->next;
        }
    }
}

void ShapeFilter(Node** shapeList)
{
    /*
    Function to filter out shapes with dimensions outside a certain range
    */
    Node* current = *shapeList;
    int sumH = 0;
    int sumW = 0;
    int sumL = 0;
    int count = 0;

    // Calculate averages for height, width, and length
    while (current != NULL)
    {
        sumH += current->data->h;
        sumW += current->data->w;
        sumL += current->data->Len;
        count++;
        current = current->next;
    }

    double averageH = (double)sumH / count;
    double averageW = (double)sumW / count;
    double averageL = (double)sumL / count;

    current = *shapeList;
    int i = 0;

    // Filter shapes based on a threshold relative to the averages
    while (current != NULL)
    {
        Node* next = current->next;
        int h = current->data->h;
        int w = current->data->w;
        int l = current->data->Len;

        if (h > 5 * averageH ||
            h < 0.1 * averageH ||
            w > 5 * averageW ||
            w < 0.1 * averageW ||
            l > 5 * averageL ||
            l < 0.1 * averageL)
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

Node* ArrayToNode(Node** shapeList, int* visited, int id)
{
    /*
    Function to convert an array of visited shapes to a linked list
    */
    Node* res = NULL;
    Node* c = *shapeList;
    while (c != NULL)
    {
        if (visited[c->data->id - 1] == id)
        {
            Node* n = NewNode(c->data);
            AddNode(&res, n);
        }
        c = c->next;
    }
    return res;
}

Node** CreateCluster(Node** shapeList, int* size, SDL_Surface* surface)
{
    /*
    Function to create a cluster list from a shape list
    */
    int n = LenNode(shapeList);

    Node* c = *shapeList;
    int* visited = calloc(n,sizeof(int));
    int i = 1;
    int count = 0;

    // For each shape, find and store clusters
    while (c != NULL)
    {
        if(visited[c->data->id - 1] != 0)
        {
            c = c->next;
            continue;
        }
        FindCluster(&visited, shapeList, c->data,count + 1);
        count++;
        i++;
        c = c->next;

    }

    Node** clusterList = (Node**)malloc(count * sizeof(Node*));
    for(int i = 0; i < count; i++)
    {
        clusterList[i] = ArrayToNode(shapeList, visited, i + 1);
    }
    free(visited);
    *size = count;
    return clusterList;
}

void FindCluster(int** visited, Node** shapeList, Shape* shape,int id)
{
    /*
    Recursive function to find clusters of shapes based on height and distance thresholds
    */   
    if ((*visited)[(shape->id) - 1] == 0)
    {
        (*visited)[(shape->id) - 1] = id;
        Shape* s = shape;
        printf("id: %i\n",id);
        while(s!=NULL)
        {   
            double avgH = 0;
            double avgW = 0;
            AverageClusterSize(shapeList, visited,id, &avgH, &avgW);
            s = FindNearestShape(shapeList, shape, visited, shape->h * 5,avgH,id);
            if(s!=NULL)
            {
                printf("Shapeid: %i CLuster id %i Actual Id: %i\n",s->id,(*visited)[s->id - 1],id);
                if((*visited)[s->id - 1] == 0)
                {
                    FindCluster(visited, shapeList, s, id);
                }
                else if((*visited)[s->id - 1] != id)
                {
                    printf("between\n");
                    int OldId = (*visited)[s->id - 1];
                    for(int i = 0; i < LenNode(shapeList); i++)
                    {
                        if((*visited)[i] == OldId)
                        {
                            (*visited)[i] = id;
                        }
                    }
                    (*visited)[s->id - 1] = id;
                }
                else{
                }
                printf("Shapeid: %i CLuster id %i Actual Id: %i\n\n",s->id,(*visited)[s->id - 1],id);
            }
        }
    }
}


Node** ClusterFilter(Node** clusterList, int* size)
{
    /*
    Function to filter clusters, keeping only those above a certain average size
    */
    if (*size > 2)
    {
        double sumSize = 0;
        for (int i = 0; i < *size; i++)
        {
            sumSize += ListSum(clusterList[i]);
        }
        double avSize = sumSize / (double)*size;
        int k = 0;

        for (int i = 0; i < *size; i++)
        {
            if (ListSum(clusterList[i]) < avSize)
            {
                FreeNodeList(&clusterList[i], 0);
                clusterList[i] = NULL;
            }
            else
            {
                k++;
            }
        }
        clusterList = ReduceArray(clusterList, size, k);// Create a new list with only the valid cluster
    }
    return clusterList;
}

int isShapeAline(Shape* s1, Shape* s2, int MaxAngle)
{
    // Check horizontal alignment (0° or 180° with MaxAngle tolerance)
    if (s2->Cx>s1->Cx-MaxAngle && s2->Cx<s1->Cx+MaxAngle)
    {
        return 1; // The shapes are horizontally aligned
    }
    return 0; // The shapes are not horizontally aligned
}


Shape* FindNearestShape(Node** shapeList, Shape* s, int** visited, int MaxDist, double avH, int id)
{
    /*
    Function to find the nearest shape to a given shape within certain thresholds
    */
    double minDist = INFINITY; // Use a large initial value for minimum distance
    Shape* closestShape = NULL;
    Node* current = *shapeList;

    while (current != NULL)
    {
        Shape* currentShape = current->data;

        // Skip the shape itself and already visited shapes
        if (currentShape->id == s->id || (*visited)[currentShape->id - 1] == id)
        {
            current = current->next;
            continue;
        }

        double dist = FindLowestDist(s, currentShape);
        int h = currentShape->h;
        double thresholdH = 5.0;

        // Check alignment, distance, and height thresholds
        if (isShapeAline(s, currentShape, 10) &&
            dist < minDist &&
            dist <= MaxDist &&
            h > avH - thresholdH &&
            h < avH + thresholdH)
        {
            minDist = dist;
            closestShape = currentShape;
        }

        current = current->next;
    }

    return closestShape;
}


void ProcessGrid(SDL_Surface *surface) 
{
    /*
    Main function to process the grid in an SDL_Surface
    */
    int width = surface->w;
    int height = surface->h;
    int** Map;
    int** surf;

    SDL_LockSurface(surface);

    // Malloc the two matrix
    MallocMatrix(&Map, height, width);
    MallocMatrix(&surf, height, width);

    //init the two matrix with base value
    InitMatrix(surface, &Map, &surf);

    Node* shapeList = NULL;
    int id = 0;

    // Loop through each pixel to identify shapes
    for (int j = 0; j < height; j++) 
    {
        for (int i = 0; i < width; i++) 
        {
            if (surf[j][i] == 255 && Map[j][i] == 0) 
            {
                id++;
                Shape* s = CreateShape(id, j, i);
                FindShape(s, surf, Map, j, i, height, width);
                ComputeShape(s);

                // Add valid shapes to the shape list
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

    FreeMatrix(surf, height);
    
    SDL_Surface* temp_surface = DuplicateSurface(surface);
    Draw(temp_surface, shapeList, 177, 0, 0);
    SDL_SaveBMP(temp_surface, "output/imgFindShape.bmp");
    SDL_FreeSurface(temp_surface);

    ShapeFilter(&shapeList);

    temp_surface = DuplicateSurface(surface);
    Draw(temp_surface, shapeList, 177, 0, 0);
    SDL_SaveBMP(temp_surface, "output/imgShapeFilter.bmp");
    SDL_FreeSurface(temp_surface);
    
    int size = 0;
    Node** clusterList = CreateCluster(&shapeList, &size,surface);

    temp_surface = DuplicateSurface(surface);
    DrawList(temp_surface, clusterList, size);
    SDL_SaveBMP(temp_surface, "output/imgFindCluster.bmp");
    SDL_FreeSurface(temp_surface);
    
    clusterList = ClusterFilter(clusterList, &size);

    /*
    for (int i = 0; i < size; i++)
    {
        AdjustList(&clusterList[i]);
    }

    DrawList(surface, clusterList, size);
    */
    /*
    for (int i = 0; i < size; i++)
    {
        char d[2048];
        sprintf(d, "mkdir -p output/letter/Cluster_%i", i);
        system(d);
        
        Node* c = clusterList[i];
        while (c != NULL)
        {
            char s[2048];
            sprintf(s, "output/letter/Cluster_%i/Letter_%i.bmp", i, c->data->id);
            SDL_Surface* crop_surface = cropLetter(c->data, Map);
            crop_surface = resize_surface(crop_surface);
            SDL_SaveBMP(crop_surface,s);
            c = c->next;
        }
        
        FreeNodeList(&clusterList[i], 0);
    }*/

    FreeMatrix(Map, height);
    for(int i = 0; i < size; i++)
    {
        FreeNodeList(&clusterList[i], 0);
    }
    free(clusterList);
    FreeNodeList(&shapeList, 1);

    SDL_UnlockSurface(surface);
}

