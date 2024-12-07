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

Node** CreateLine(Node** shapeList, int* size)
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
        FindLine(&visited, shapeList, c->data,count + 1);
        count++;
        i++;
        c = c->next;

    }

    Node** LineList = (Node**)malloc(count * sizeof(Node*));
    int nbValid = 0;
    for(int i = 0; i < count; i++)
    {
        LineList[i] = ArrayToNode(shapeList, visited, i + 1);
        if(LineList[i]!=NULL)
        {
            nbValid++;
        }
    }
    Node** res = (Node**)malloc(nbValid*sizeof(Node*));
    int k = 0;
    for(int i = 0; i<count; i++)
    {
        if(LineList[i]!=NULL)
        {
            res[k] = LineList[i];
            k++;
        }
    }
    free(visited);
    free(LineList);
    *size = k;
    return res;
}

void FindLine(int** visited, Node** shapeList, Shape* shape,int id)
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
            s = FindNearestShape(shapeList, shape, visited, shape->h * 3,avgH,id);
            if(s!=NULL)
            {
                //printf("Shapeid: %i CLuster id %i Actual Id: %i\n",s->id,(*visited)[s->id - 1],id);
                if((*visited)[s->id - 1] == 0)
                {
                    FindLine(visited, shapeList, s, id);
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

Node** LineToCluster(Node** ClusterList, int* visited, int id, int* ClusterSize, int size)
{
    Node** res = malloc(sizeof(Node*));
    int count = 0;
    for(int i = 0; i<size; i++)
    {
        if(visited[i] == id)
        {
            count++;
            res = realloc(res,count*sizeof(Node*));
            res[count-1] = ClusterList[i];   
        }
    }
    *ClusterSize = count;
    return res;
    
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

Node*** CreateClusters(Node** clusterList, int* size,int** ClusterSize)
{
    Node*** res = (Node***)malloc(sizeof(Node**));
    int* visited = (int*)calloc((*size),sizeof(int));
    int id = 1;
    int nbId = 0;
    for(int i = 0; i < (*size); i++)
    {
        Node* line = clusterList[i];
        if((visited)[i] != 0 || line == NULL)
        {
            continue;
        }
        (visited)[i] = id;
        for(int j = 0; j<(*size); j++)
        {
                Node* testedLine = clusterList[j];
                if(testedLine == NULL)
                {
                    continue;
                }
                Shape* shape1;
                Shape* shape2;
                if(LenNode(&line) > LenNode(&testedLine))
                {
                    shape1 = GetMainShape(line->data,testedLine);
                    shape2 = line->data;
                }
                else
                {
                    shape1 = line->data;
                    shape2 = GetMainShape(shape1,testedLine);
                }
                if(FindLowestDist(shape1,shape2)<(shape1->h*4))//&& LenNode(&cluster2) == LenNode(&cluster))
                {
                    //DrawLine(surface,shape1,shape2,255,0,0);
                    if(isShapeAline_Vertical(shape1,shape2, 5))
                    {
                        if((visited)[j] == 0)
                        {
                            (visited)[j] = id;
                            line = clusterList[j];
                        }
                        else if((visited)[j]!=id)
                        {
                            int oldId = (visited)[j];
                            for(int l = 0; l<(*size); l++)
                            {
                                if((visited)[l]==oldId)
                                {
                                    (visited)[l] = id;
                                }
                            }
                            (visited)[j] = id;
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
        id++;
        nbId++;
    }
    for(int i = 0; i<*size; i++)
    {
        if(visited[i]==0)
        {
            //FreeNodeList(&clusterList[i],0);
        }
    }
    int* Ids = malloc(sizeof(int));
    int k = 0;
    for(int i = 0; i<*size; i++)
    {
        if(!contain(Ids,visited[i],k))
        {
            k++;
            Ids = realloc(Ids,k*sizeof(int));
            Ids[k-1] = visited[i];
        }
    }
    *ClusterSize = malloc(k*sizeof(int));
    for(int id = 0; id<k; id++)
    {
        //printf("ID %i\n",id);
        res = realloc(res,(id+1)*sizeof(Node**));
        int clusterSize = 0;
        res[id] = LineToCluster(clusterList,visited,Ids[id],&clusterSize,*size);
        (*ClusterSize)[id] = clusterSize;
        //printf("ClusterSize %i\n",clusterSize);

    }
    for(int i = 0; i<*size; i++)
    {
        if(!contain(Ids,visited[i],k))
        {
            //printf("Free %i\n",i);
            FreeNodeList(&clusterList[i],0);
        }
    }
    //printf("visited: ");
    for(int i = 0; i<*size; i++)
    {
        //printf("%i ",visited[i]);
    }
    //printf("\n");
    //printf("Ids: ");
    for(int i = 0; i<k; i++)
    {
        //printf("%i ",Ids[i]);
    }
    //printf("\n");
    free(visited);
    free(Ids);
    *size = k;
    return res;
}



void ClusterFilter(Node**** clusterList, int* size,int** ClusterSize)
{
    double avSize = 0;
    for(int i = 0; i<*size; i++)
    {
        avSize += (double)(*ClusterSize)[i];
    }
    avSize = avSize/(double)(*size);

    for(int i = 0; i<*size; i++)
    {
        if((*ClusterSize)[i]<avSize/2 || (*ClusterSize)[i]<5 )//|| (*ClusterSize)[i]>21)
        {

            for(int j = 0; j<(*ClusterSize)[i]; j++)
            {
                if((*clusterList)[i][j]!=NULL)
                {
                    FreeNodeList(&(*clusterList)[i][j],0);
                }
            }
            free((*clusterList)[i]);
            (*clusterList)[i] = NULL;
        }
        else
        {
            
            int avClusterSize = 0;
            for(int j = 0; j<(*ClusterSize)[i]; j++)
            {
                avClusterSize += LenNode(&(*clusterList)[i][j]);
            }
            avClusterSize = avClusterSize/(double)(*ClusterSize)[i];
            int newsize = 0;
            for(int j = 0; j<(*ClusterSize)[i]; j++)
            {
                if(LenNode(&(*clusterList)[i][j])<3)
                {
                    FreeNodeList(&(*clusterList)[i][j],0);
                    (*clusterList)[i][j] = NULL;
                }
                else
                {
                    newsize++;
                }
                
            }
            

        }
    }



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
        if (isShapeAline_Horizontal(s, currentShape, 5) &&
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

void writeGrid(Letter*** Grid,int nbOfLine, int LineSize)
{
    FILE* file = fopen("grid", "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    for (int i = 0; i < nbOfLine; i++) {
        for (int j = 0; j < LineSize; j++) {
            fputc(Grid[i][j]->letter, file);
        }
        fputc('\n', file); // Ajouter un retour à la ligne après chaque ligne de la matrice
    }

    fclose(file);
}

void ProcessSolver(Node**** Clusters, int* size, int* ClusterSize, int** Map)
{
    Node*** GridList = *Clusters;//call the function
    place(GridList,*size,ClusterSize);
    Node** GridN = GridList[0];
    Letter*** Grid = malloc(ClusterSize[0]*sizeof(Letter**));
    int GridSize = 0;
    int WordCount = 0;
    int* WordSize = malloc(sizeof(int));
    Letter*** LetterList = malloc(sizeof(Letter**));
    char** WordList = malloc(sizeof(char*));

    //init value Neural Network;
    int nbInputs;
	int nbHiddenNodes;
	int nbOutputs;

	double LearningRate;

    double *hiddenLayerBias;
    double *outputLayerBias;

    double **hiddenWeights;
    double **outputWeights;
    
    LoadData("data.txt",&hiddenLayerBias, &outputLayerBias, &hiddenWeights, &outputWeights, &nbInputs, &nbHiddenNodes, &nbOutputs, &LearningRate);

    //Load Grid
    printf("GridSize %i\n",ClusterSize[0]);
    for(int i = 0; i<ClusterSize[0]; i++)
    {
        printf("Line: ");
        if(GridN[i]==NULL)
        {
            continue;
            printf("Line %i NULL\n",i);
        }
        if(GridSize == 0)
        {
            GridSize = LenNode(&GridN[i]);
        }
        Grid[i] = malloc(GridSize*sizeof(Letter));
        int j = 0;
        for(Node* c = GridN[i]; c!=NULL; c = c->next)
        {   
            Letter* l = malloc(sizeof(Letter));
            SDL_Surface* surface = cropLetter(c->data,Map);
            surface = resize_surface(surface);
            //printf("Load nb %i\n",j);
            char letter = LetterRecognition(surface,nbInputs,nbHiddenNodes,nbOutputs,LearningRate,hiddenLayerBias,outputLayerBias,hiddenWeights,outputWeights);
            printf("%c",letter);
            l->letter = letter;
            l->x = c->data->Cx;
            l->y = c->data->Cy;
            Grid[i][j] = l;
            j++;
            SDL_FreeSurface(surface);
        }
        printf("\n");
    }
    
    for(int i = 1; i<*size; i++)
    {
        if(GridList[i]==NULL)
        {
            continue;
        }
        for(int j = 0; j<ClusterSize[i]; j++)
        {
            if(GridList[i][j]==NULL)
            {
                continue;
            }
            WordCount++;
            LetterList = realloc(LetterList,WordCount*sizeof(Letter**));
            WordSize = realloc(WordSize,WordCount*sizeof(int));
            WordList = realloc(WordList,WordCount*sizeof(char*));
            char* word = malloc(sizeof(char));
            int sizeofword = 0;
            int id = 0;
            LetterList[WordCount-1] = malloc(sizeof(Letter*));
            for(Node* c = GridList[i][j]; c!=NULL; c = c->next)
            {
                Letter* l = malloc(sizeof(Letter));
                SDL_Surface* surface = cropLetter(c->data,Map);
                surface = resize_surface(surface);
                char letter = LetterRecognition(surface,nbInputs,nbHiddenNodes,nbOutputs,LearningRate,hiddenLayerBias,outputLayerBias,hiddenWeights,outputWeights);
                sizeofword++;
                word = realloc(word,sizeofword*sizeof(char));
                word[sizeofword-1] = letter;
                l->letter = letter;
                l->x = c->data->Cx;
                l->y = c->data->Cy;
                LetterList[WordCount-1] = realloc(LetterList[WordCount-1],sizeofword*sizeof(Letter*));
                LetterList[WordCount-1][sizeofword-1] = l;

                id++;
            }
            word = realloc(word,(sizeofword+1)*sizeof(char));
            word[sizeofword] = '\0';
            WordList[WordCount-1] = word; 
            WordSize[WordCount-1] = sizeofword;



        }

    }
    printf("\n");
    printf("WordList:\n");
    for(int i = 0; i<WordCount; i++)
    {
        //for(int j = 0; j<WordSize[i]; j++)
        printf("%s\n",WordList[i]);
    }
    printf("\n");
    
    writeGrid(Grid,ClusterSize[0],GridSize);

    int* Start;
    int* End;
    Start = NULL;
    End = NULL;

    SDL_Surface* surface = SDL_LoadBMP("output/original.bmp");
    for(int i = 0; i<WordCount; i++)
    {
        int e = solver(WordList[i],&Start,&End);
        if(e==-1)
        {
            free(Start);
            free(End);
            continue;
        }
        Letter* StartLetter = Grid[Start[1]][Start[0]];
        Letter* EndLetter = Grid[End[1]][End[0]];
        int r,g,b;
        getRandomColor(&r,&g,&b,i,WordCount*2);
        drawSolution(surface,StartLetter->x,StartLetter->y,EndLetter->x,EndLetter->y,r,g,b);
        
        Letter* First = LetterList[i][0];
        Letter* Last = LetterList[i][WordSize[i]-1];
        drawSolution(surface,First->x,First->y,Last->x,Last->y,r,g,b);
        
        printf("StartLetter: %c\n",StartLetter->letter);
        printf("EndLetter: %c\n",EndLetter->letter);
        free(Start);
        free(End);
        
    }
    SDL_SaveBMP(surface,"output/imgFinal.bmp");
    SDL_FreeSurface(surface);


    FreeMatrix(hiddenWeights, nbInputs);
    FreeMatrix(outputWeights, nbHiddenNodes);
    free(hiddenLayerBias);
    free(outputLayerBias);

    for(int i = 0; i<ClusterSize[0];i++)
    {
        for(int j = 0; j<GridSize ;j++)
        {
            free(Grid[i][j]);
        }
        free(Grid[i]);
    }
    free(Grid);
    for(int i = 0; i<WordCount; i++)
    {
        for(int j = 0; j<WordSize[i]; j++)
        {
            free(LetterList[i][j]);
        }
        free(LetterList[i]);
        free(WordList[i]);
    }
    free(LetterList);
    free(WordSize);
    free(WordList);


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
    GMallocMatrix(&Map, height, width);
    GMallocMatrix(&surf, height, width);

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

    GFreeMatrix(surf, height);
    
    SDL_Surface* temp_surface = DuplicateSurface(surface);
    Draw(temp_surface, shapeList, 177, 0, 0,0);
    SDL_SaveBMP(temp_surface, "output/imgFindShape.bmp");
    SDL_FreeSurface(temp_surface);

    ShapeFilter(&shapeList);

    temp_surface = DuplicateSurface(surface);
    Draw(temp_surface, shapeList, 177, 0, 0,0);
    SDL_SaveBMP(temp_surface, "output/imgShapeFilter.bmp");
    SDL_FreeSurface(temp_surface);
    
    int size = 0;
    Node** clusterList = CreateLine(&shapeList, &size);

    temp_surface = DuplicateSurface(surface);
    for(int i = 0; i<size; i++)
    {
        int r,g,b;
        getRandomColor(&r, &g, &b, i, size);
        Draw(temp_surface,clusterList[i],r,g,b,1);
    }
    SDL_SaveBMP(temp_surface, "output/imgFindCluster.bmp");
    SDL_FreeSurface(temp_surface);




   


    int* ClusterSize = NULL;

    Node*** Clusters = CreateClusters(clusterList,&size,&ClusterSize);

    ClusterFilter(&Clusters, &size, &ClusterSize);

    //printf("Size %i\n",size);
    for(int i = 0; i<size; i++)
    {
        if(Clusters[i]==NULL)
        {
            //printf("Cluster %i NULL\n",i);
            continue;
        }
        //printf("Cluster %i Size %i\n",i,ClusterSize[i]);
        int r,g,b;
        getRandomColor(&r, &g, &b, i, size);
        if(Clusters[i][0]==NULL)
        {
                //printf("Cluster %i NULL!!!!!!!!!!!!!!\n",0);
                continue;
        }
        Draw(surface,Clusters[i][0],r,g,b,1);
        for(int j = 1; j<ClusterSize[i]; j++)
        {
            if(Clusters[i][j]==NULL || Clusters[i][j-1]==NULL)
            {
                //printf("Cluster %i NULL!!!!!!!!!!!!!!\n",j);
                continue;
            }
            Draw(surface,Clusters[i][j],r,g,b,1);
            DrawLine(surface,Clusters[i][j-1]->data,Clusters[i][j]->data,0,0,255);
        }
        
    }
    //printf("Start ProcessSolver\n");
    ProcessSolver(&Clusters,&size,ClusterSize,Map);
    /*
    //init value Neural Network;
    int nbInputs;
	int nbHiddenNodes;
	int nbOutputs;

	double LearningRate;

    double *hiddenLayerBias;
    double *outputLayerBias;

    double **hiddenWeights;
    double **outputWeights;
    
    LoadData("data.txt",&hiddenLayerBias, &outputLayerBias, &hiddenWeights, &outputWeights, &nbInputs, &nbHiddenNodes, &nbOutputs, &LearningRate);

    printf("WordList:\n");
    for(int i = 0; i<size; i++)
    {
        if(Clusters[i]==NULL)
        {
            continue;
        }
        for(int j = 0; j<ClusterSize[i]; j++)
        {
            if(Clusters[i][j]==NULL)
            {
                continue;
            }
            printf("Word: ");
            int m = 0;
            for(Node* k = Clusters[i][j]; k!=NULL; k = k->next)
            {
                SDL_Surface* surface = cropLetter(k->data,Map);
                surface = resize_surface(surface);
                char* cmd = NULL;
                asprintf(&cmd, "output/letter/imgLetter%i_%i.bmp",j,m);
                SDL_SaveBMP(surface, cmd);
                free(cmd);
                //printf("Load nb %i\n",j);
                char letter = LetterRecognition(surface,nbInputs,nbHiddenNodes,nbOutputs,LearningRate,hiddenLayerBias,outputLayerBias,hiddenWeights,outputWeights);
                printf("%c",letter);
                SDL_FreeSurface(surface);
                m++;
            }
            printf("\n");
            
        }
    }
    
    FreeMatrix(hiddenWeights, nbInputs);
    FreeMatrix(outputWeights, nbHiddenNodes);
    free(hiddenLayerBias);
    free(outputLayerBias);
    */

    GFreeMatrix(Map, height);
    //free(ClusterGrid);
    /*
    for(int i = 0; i < size; i++)
    {
        if(clusterList[i]!=NULL)
        {
            FreeNodeList(&clusterList[i], 0);
        }
    }
    */
    free(clusterList);
    FreeNodeList(&shapeList, 1);
    for(int i = 0; i<size; i++)
    {
        if(Clusters[i]==NULL)
        {
            continue;
        }
        for(int j = 0; j<ClusterSize[i]; j++)
        {
            if(Clusters[i][j]!=NULL)
            {
                FreeNodeList(&Clusters[i][j],0);
            }
        }
        free(Clusters[i]);
    }
    free(Clusters);
    free(ClusterSize);

    SDL_UnlockSurface(surface);
}

