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
            err(1,"the value is not a double: %c\n",str[i]);
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



void WriteData(char filename[], double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights, int nbInputs, int nbHiddenNodes, int nbOutputs, double LearningRate)
{
	FILE *file = fopen(filename,"w");
	const char com1[] = "// Hidden layer data, first line for bias, others for weights\n";
	const char com2[] = "// Output layer data, first line for bias, others for weights\n";

	if(file == NULL)
	{
		err(1,"Error opening file %s\n",filename);
	}

	fprintf(file,"%i|%i|%i|%f\n",nbInputs,nbHiddenNodes,nbOutputs,LearningRate);
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

