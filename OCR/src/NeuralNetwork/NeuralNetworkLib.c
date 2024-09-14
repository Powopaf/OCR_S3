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
