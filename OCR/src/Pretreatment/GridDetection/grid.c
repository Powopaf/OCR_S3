#include "grid.h"
#include <unistd.h>

void AverageClusterSize(Node** cluster, double* avHeight, double* avWidth)
{
    /*
    Function to calculate the average height and width of shapes in a cluster
    */
    if (cluster == NULL)
    {
        return;
    }
    int sumh = 0;
    int sumw = 0;
    int count = 0;
    Node* lst = *cluster;

    // go through the list and accumulate heights and widths
    while (lst != NULL)
    {
        Shape* data = lst->data;
        sumh += data->h;
        sumw += data->w;
        count++;
        lst = lst->next;
    }
    *avHeight = sumh / (double)count;
    *avWidth = sumw / (double)count;
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

Node** CreateCluster(Node** shapeList, int* size)
{
    /*
    Function to create a cluster list from a shape list
    */
    int n = LenNode(shapeList);
    Node** clusterList = (Node**)malloc(n * sizeof(Node*));

    Node* c = *shapeList;
    Node* visited = NULL;
    int i = 1;
    int count = 0;

    // For each shape, find and store clusters
    while (c != NULL)
    {
        Node* cluster = NULL;
        FindCluster(&visited, &cluster, shapeList, c->data);
        clusterList[i - 1] = cluster;
        if (cluster != NULL)
        {
            count++;
        }
        i++;
        c = c->next;
    }

    FreeNodeList(&visited, 0);
    *size = n;
    return ReduceArray(clusterList, size, count);
}

void FindCluster(Node** visited, Node** cluster, Node** shapeList, Shape* shape)
{
    /*
    Recursive function to find clusters of shapes based on height and distance thresholds
    */   
    if (!ContainsNode(*visited, shape))
    {
        Node* nv = NewNode(shape);
        Node* nc = NewNode(shape);
        AddNode(visited, nv);
        AddNode(cluster, nc);

        Node* current = *shapeList;
        while (current != NULL)
        {
            if (shape->id != current->data->id)
            {
                double threshold = 1.5;
                double h = shape->h;
                double avHeight;
                double avWidth;
                AverageClusterSize(cluster, &avHeight, &avWidth);

                // Check if shape meets height and distance thresholds
                if (h < avHeight + threshold && h > avHeight - threshold && 
                    FindLowestDist(shape, current->data) < (avHeight + avWidth))
                {
                    FindCluster(visited, cluster, shapeList, current->data);
                }
            }
            current = current->next;
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
    Node** clusterList = CreateCluster(&shapeList, &size);

    temp_surface = DuplicateSurface(surface);
    DrawList(temp_surface, clusterList, size);
    SDL_SaveBMP(temp_surface, "output/imgFindCluster.bmp");
    SDL_FreeSurface(temp_surface);
    
    clusterList = ClusterFilter(clusterList, &size);

    for (int i = 0; i < size; i++)
    {
        AdjustList(&clusterList[i]);
    }

    DrawList(surface, clusterList, size);

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
    }

    FreeMatrix(Map, height);
    free(clusterList);
    FreeNodeList(&shapeList, 1);

    SDL_UnlockSurface(surface);
}

