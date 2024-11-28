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
        //printf("id %i visited %i\n",c->data->id,(*visited)[c->data->id-1]);
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
    if(res == NULL)
    {
        printf("Error in ArrayToNode\n");
    }
    return res;
}

Node** CreateCluster(Node** shapeList, int* size)
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
        //printf("id: %i\n",id);
        while(s!=NULL)
        {   
            double avgH = 0;
            double avgW = 0;
            AverageClusterSize(shapeList, visited,id, &avgH, &avgW);
            s = FindNearestShape(shapeList, shape, visited, shape->h * 5,avgH,id);
            if(s!=NULL)
            {
                //printf("Shapeid: %i CLuster id %i Actual Id: %i\n",s->id,(*visited)[s->id - 1],id);
                if((*visited)[s->id - 1] == 0)
                {
                    FindCluster(visited, shapeList, s, id);
                }
                else if((*visited)[s->id - 1] != id)
                {
                    //printf("between\n");
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
                //printf("Shapeid: %i CLuster id %i Actual Id: %i\n\n",s->id,(*visited)[s->id - 1],id);
            }
        }
    }
}

int isShapeAline_Horizontal(Shape* s1, Shape* s2, int MaxAngle)
{
    // Check horizontal alignment (0° or 180° with MaxAngle tolerance)
    if (s2->Cx>s1->Cx-MaxAngle && s2->Cx<s1->Cx+MaxAngle)
    {
        return 1; // The shapes are horizontally aligned
    }
    return 0; // The shapes are not horizontally aligned
}

int isShapeAline_Vertical(Shape* s1, Shape* s2, int MaxAngle)
{
    // Check vertical alignment (90° or 270° with MaxAngle tolerance)
    if (s2->Cy>s1->Cy-MaxAngle && s2->Cy<s1->Cy+MaxAngle)
    {
        return 1; // The shapes are vertically aligned
    }
    return 0; // The shapes are not vertically aligned
}

Shape* GetMainShape(Shape* s, Node* cluster)
{
    // Get the main shape in a cluster based on the lowest distance
    Node* c = cluster;
    Shape* res = c->data;
    double minDist = distance(s->Cx,s->Cy,res->Cx,res->Cy);
    while (c != NULL)
    {
        double dist = distance(s->Cx,s->Cy,c->data->Cx,c->data->Cy);
        if (dist < minDist)
        {
            minDist = dist;
            res = c->data;
        }
        c = c->next;
    }
    return res;
}

int ClusterFilter(Node** clusterList, int* size,int** visited,SDL_Surface* surface)
{
    //Node*** res = (Node***)malloc(sizeof(Node**));
    *visited = (int*)calloc((*size),sizeof(int));
    int k = 1;
    int nbId = 0;
    for(int i = 0; i < (*size); i++)
    {
        Node* cluster = clusterList[i];
        if((*visited)[i] != 0 || cluster == NULL)
        {
            continue;
        }
        (*visited)[i] = k;
        for(int j = 0; j<(*size); j++)
        {
                Node* cluster2 = clusterList[j];
                if(cluster2 == NULL)
                {
                    continue;
                }
                Shape* shape1 = cluster->data;
                Shape* shape2 = GetMainShape(shape1,cluster2);
                if(FindLowestDist(shape1,shape2)<(shape1->h*3))//&& LenNode(&cluster2) == LenNode(&cluster))
                {
                    //DrawLine(surface,shape1,shape2,255,0,0);
                    if(isShapeAline_Vertical(shape1,shape2, 15))
                    {
                        if((*visited)[j] == 0)
                        {
                            (*visited)[j] = k;
                            cluster = clusterList[j];
                        }
                        else if((*visited)[j]!=k)
                        {
                            int oldId = (*visited)[j];
                            for(int l = 0; l<(*size); l++)
                            {
                                if((*visited)[l]==oldId)
                                {
                                    (*visited)[l] = k;
                                }
                            }
                            (*visited)[j] = k;
                            nbId--;
                        }
                        //DrawLine(surface,shape1,shape2,255,0,0);
                        
                    }
                }
                else
                {
                    //DrawLine(surface,shape1,shape2,0,255,0);
                }
        }
        k++;
        nbId++;
    }
    printf("%i\n",nbId);

    return nbId;
    
}

Node*** AdjusteCluster(Node** ClusterList,int** visited,int* Ids, int* size, int* nbId)
{
    float avSize = 0;
    for(int i = 0; i<*nbId; i++)
    {
        avSize += (float)ListSum(ClusterList[i]);
    }
    avSize = avSize/(float)(*nbId);
    printf("avSize = %f\n",avSize);

    Node*** Res = malloc(sizeof(Node**));
    int* ClusterSize = malloc(sizeof(int));
    int k = 0;
    for(int i = 0; i<*nbId; i++)
    {
        float sum = 0;
        int nbLine = 0;
        Node** Line = malloc(sizeof(Node*));
        for(int j = 0; j<*size; j++)
        {
            if((*visited)[j]==Ids[i] && ClusterList[j]!=NULL)
            {
                sum+=ListSum(ClusterList[j]);
                nbLine++;
                Line = realloc(Line,nbLine*sizeof(Node*));
                AdjustList(&ClusterList[j]);
                Line[nbLine-1] = ClusterList[j];
            }
        }
        printf("ID: %i  nbLine = %i Sum = %f\n",Ids[i],nbLine,sum);
        if(nbLine>5 && sum>avSize/2)
        {
            k++;
            Res = realloc(Res,k*sizeof(Node**));
            ClusterSize = realloc(ClusterSize,k*sizeof(Node**));
            ClusterSize[k-1] = nbLine;
            Res[k-1] = Line;
        }
        else
        {
            for(int j = 0; j<nbLine; j++)
            {
                //FreeNodeList(&Line[j],0);
            }
            //free(Line);
        }
    }
    *size = k;
    free(*visited);
    *visited = ClusterSize;
    return Res;
}

Node*** ReduceCluster(Node*** Clusters,int* size,int* ClusterSize)
{
    for(int i = 0;i<*size;i++)
    {
        int avSize = 0;
        printf("ClusterSize %i\n",ClusterSize[i]);
        int* Size = malloc(ClusterSize[i]*sizeof(int));
        int s = ClusterSize[i];;
        for(int j = 0; j<ClusterSize[i]; j++)
        {
            Size[j] = ListSum(Clusters[i][j]);
            avSize += Size[j];
        }
        avSize = avSize/(float)ClusterSize[i];
        for(int j = 0; j<ClusterSize[i]; j++)
        {
            if(Size[j]<avSize/2)
            {
                //FreeNodeList(&Clusters[i][j],0);
                Clusters[i][j] = NULL;
                s--;
            }
        }
        printf("New Size %i\n",s);
        
    }
    return Clusters;
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
        if (isShapeAline_Horizontal(s, currentShape, 15) &&
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

int mostFrequentValue(int* array, int size) {
    int maxCount = 0;    // Compteur maximum
    int mostFrequent = 0; // Valeur la plus fréquente

    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (array[i] == array[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostFrequent = array[i];
        }
    }
    return mostFrequent;
}

int GridSize(Node** clusterList, int size)
{
    /*
    Function to calculate the size of the grid based on the most frequent number of shapes in a cluster
    */
    int* sizes = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        sizes[i] = LenNode(&clusterList[i]);
    }
    int gridSize = mostFrequentValue(sizes, size);
    free(sizes);
    return gridSize;
}

int contain(int* lst, int i, int size)
{
    for(int j = 0; j<size; j++)
    {
        if(lst[j] == i)
        {
            return 1;
        }
    }
    return 0;
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

    /*
    int gridSize = GridSize(clusterList, size);

    Node** ClusterGrid = (Node**)malloc(sizeof(Node*));
    int k = 0;
    for(int i = 0; i < size; i++)
    {
        if(LenNode(&clusterList[i]) == gridSize)
        {
            ClusterGrid = (Node**)realloc(ClusterGrid, (k + 1) * sizeof(Node*));
            ClusterGrid[k] = clusterList[i];
            k++;
        }
    }*/
    int* visited = NULL;
    int nbId = ClusterFilter(clusterList, &size,&visited,surface);
    
    int* Ids = malloc(sizeof(int));
    int k = 0;
    for(int i = 0; i<size; i++)
    {
        if(!contain(Ids,visited[i],k))
        {
            k++;
            Ids = realloc(Ids,k*sizeof(int));
            Ids[k-1] = visited[i];
        }
    }

    Node*** Clusters = AdjusteCluster(clusterList,&visited,Ids,&size,&k);
    Clusters = ReduceCluster(Clusters,&size,visited);
    printf("sizes:%i\n",size);
    for(int i = 0; i<size; i++)
    {
        printf(" %i\n",visited[i]);
    }
    printf("\n");
    for(int i = 0; i<size; i++)
    {
        DrawList(surface,Clusters[i],visited[i]);
    }


    /*   
        Clusters = liste des cluster
        Cluster[i] = liste des lignes
        Cluster[i][j] = liste des shapes dans la lignes
    */

    /*
    for (int i = 0; i < size; i++)
    {
        AdjustList(&clusterList[i]);
    }
    */
    //DrawList(surface, clusterList, size);
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


    //Gros pb de leak je m'en occuperais plus tard

    FreeMatrix(Map, height);
    //free(ClusterGrid);
    for(int i = 0; i < size; i++)
    {
        FreeNodeList(&clusterList[i], 0);
    }
    free(clusterList);
    FreeNodeList(&shapeList, 1);

    SDL_UnlockSurface(surface);
}

