#include "NeuralNetwork.h"

//sigmoid function
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

//derivative sigmoid function
double dsigmoid(double x)
{
    return x * (1 - x);
}

double init_weights()
{
    return ((double)rand() / RAND_MAX);
}

int ReadInt(char str[])
{
	int resultat = 0;
    int signe = 1;
	int i = 0;
    if (str[i] == '-') 
	{
        signe = -1;
        i++;
    }

    while (str[i] != '\0') 
	{
        if (str[i] >= '0' && str[i] <= '9') 
		{
            resultat = resultat * 10 + (str[i] - '0');
        }
		else 
		{
            err(1,"the value is not a int: %c\n",str[i]);
        }
        i++;
    }

    return resultat * signe;
}

double ReadDouble(char str[]) 
{
    double resultat = 0.0;
    double fraction = 0.0;
    int signe = 1;
    int partie_fractionnaire = 0;
    double diviseur = 10.0;
	int i = 0;

    if (str[i] == '-') 
	{
        signe = -1;
        i++;
    }

    while (str[i] != '\0') 
	{
        if (str[i] == '.') 
		{
            partie_fractionnaire = 1;
        } 
		else if (str[i] >= '0' && str[i] <= '9') 
		{
            if (!partie_fractionnaire) 
			{
                resultat = resultat * 10 + (str[i] - '0');
            } 
			else 
			{
                fraction = fraction + (str[i] - '0') / diviseur;
                diviseur *= 10;
            }
        } 
		else 
		{
            err(1,"the value is not a double: %c, dans la chaine: %s\n",str[i],str);
        }
        i++;
    }

    return signe * (resultat + fraction);
}

void MallocArray(double **arr,int size)
{
	*arr = (double *)malloc(size * sizeof(double));
	if (*arr == NULL)
    {
        err(1,"Erreur d'allocation de mémoire\n");
    }
}

void MallocMatrix(double ***arr, int sizex, int sizey)
{
	*arr = (double **)malloc(sizex * sizeof(double *));
	
	if (*arr == NULL) 
	{
        err(1,"Erreur d'allocation de mémoire\n");
    }

	for(int i = 0; i<sizex; i++)
	{
		(*arr)[i] = (double *)malloc(sizey * sizeof(double));
		if((*arr)[i] == NULL)
		{
			err(1,"Erreur d'allocation de mémoire pour la ligne %i",i);
		}
	}
}

char** Split(char *str, int* size) 
{
	// Count how many tokens (substrings) will be created
	const char delimiter = '|';
    char* strCopy = strdup(str);  // Duplicate the string as strtok modifies it
    char* token = strtok(strCopy, &delimiter);
    int count = 0;

    // Count the number of tokens
    while (token != NULL) {
        count++;
        token = strtok(NULL, &delimiter);
    }

    // Allocate memory for the array of strings
    char** result = (char**)malloc(count * sizeof(char*));

    // Reset the strCopy for the actual token extraction
    strcpy(strCopy, str);
    token = strtok(strCopy, &delimiter);
    int index = 0;

    // Extract the tokens and store them in result
    while (token != NULL) {
        result[index++] = strdup(token);
        token = strtok(NULL, &delimiter);
    }

	*size = count;

    free(strCopy);  // Free the temporary copy of the string

    return result;
}

void LoadData(char filename[],double **hiddenLayerBias, double **outputLayerBias, double ***hiddenWeights, double ***outputWeights, int *nbInputs, int *nbHiddenNodes, int *nbOutputs, double *LearningRate)
{
	FILE *file = fopen(filename,"r");

	if(file == NULL)
	{
		err(1,"Error opening file %s\n",filename);
	}

	char line[256]; //buffer for stock each line

	fgets(line, sizeof(line), file);
	int size = 0;
	char **arr = Split(line,&size);
	*nbInputs = ReadInt(arr[0]);
	*nbHiddenNodes = ReadInt(arr[1]);
	*nbOutputs = ReadInt(arr[2]);
	*LearningRate = ReadDouble(arr[3]);

	fgets(line, sizeof(line), file);// skip the first comment
	fgets(line, sizeof(line), file);// Hidden Bias;
	arr = Split(line,&size);
	MallocArray(hiddenLayerBias,*nbHiddenNodes);
	for(int i = 0; i<*nbHiddenNodes; i++)
	{
		(*hiddenLayerBias)[i] = ReadDouble(arr[i]);
	}
	MallocMatrix(hiddenWeights,*nbInputs,*nbHiddenNodes);
	for(int i = 0; i<*nbInputs; i++)
	{
		if(fgets(line, sizeof(line), file) == NULL)
        {
            err(1,"Error data is not in the correct format");
		}
		arr = Split(line,&size);
		for(int j = 0; j<*nbHiddenNodes; j++)
		{
			(*hiddenWeights)[i][j] = ReadDouble(arr[j]);
		}
	}


	fgets(line, sizeof(line), file);// skip the second comment
    fgets(line, sizeof(line), file);// Output Bias;
    arr = Split(line,&size);
    MallocArray(outputLayerBias,*nbOutputs);
    for(int i = 0; i<*nbOutputs; i++)
    {
        (*outputLayerBias)[i] = ReadDouble(arr[i]);
    }
    MallocMatrix(outputWeights,*nbHiddenNodes,*nbOutputs);
    for(int i = 0; i<*nbHiddenNodes; i++)
    {
        if(fgets(line, sizeof(line), file) == NULL)
        {
            err(1,"Error data is not in the correct format");
        }
        arr = Split(line,&size);
        for(int j = 0; j<*nbOutputs; j++)
        {
            (*outputWeights)[i][j] = ReadDouble(arr[j]);
        }
    }

	fclose(file);
}

void WriteData(char filename[], double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights, int nbInputs, int nbHiddenNodes, int nbOutputs, double LearningRate)
{
	FILE *file = fopen(filename,"w");
	const char com1[] = "// Hidden layer data, first line for bias, others for weights\n";
	const char com2[] = "// Output layer data, first line for bias, others for weights\n";

	if(file == NULL)
	{
		err(1,"Error opening file %s\n",filename);
	}

	fprintf(file,"%i|%i|%i|%f|\n",nbInputs,nbHiddenNodes,nbOutputs,LearningRate);
	fprintf(file,"%s",com1);

	for(int i = 0; i<nbHiddenNodes; i++)
	{
		fprintf(file,"%f|",hiddenLayerBias[i]);
	}
	fprintf(file,"\n");

	for(int i = 0; i<nbInputs; i++)
	{
		for(int j = 0; j<nbHiddenNodes; j++)
		{
			fprintf(file,"%f|",hiddenWeights[i][j]);
		}
		fprintf(file,"\n");
	}
	
	fprintf(file,"%s",com2);

	for(int i = 0; i<nbOutputs; i++)
    {
        fprintf(file,"%f|",outputLayerBias[i]);
    }
    fprintf(file,"\n");

    for(int i = 0; i<nbHiddenNodes; i++)
    {
        for(int j = 0; j<nbOutputs; j++)
        {
            fprintf(file,"%f|",outputWeights[i][j]);
        }
        fprintf(file,"\n");
    }

	fclose(file);
}

