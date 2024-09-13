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

int ReadInt(const char *chaine)
{
	int resultat = 0;
    int signe = 1;

    if (*chaine == '-') 
	{
        signe = -1;
        chaine++;
    }

    while (*chaine != '\0') 
	{
        if (*chaine >= '0' && *chaine <= '9') 
		{
            resultat = resultat * 10 + (*chaine - '0');
        }
		else 
		{
            err(1,"the value is not a int: %c\n",*chaine);
        }
        chaine++;
    }

    return resultat * signe;
}

double ReadDouble(const char *chaine) 
{
    double resultat = 0.0;
    double fraction = 0.0;
    int signe = 1;
    int partie_fractionnaire = 0;
    double diviseur = 10.0;

    if (*chaine == '-') 
	{
        signe = -1;
        chaine++;
    }

    while (*chaine != '\0') 
	{
        if (*chaine == '.') 
		{
            partie_fractionnaire = 1;
        } 
		else if (*chaine >= '0' && *chaine <= '9') 
		{
            if (!partie_fractionnaire) 
			{
                resultat = resultat * 10 + (*chaine - '0');
            } 
			else 
			{
                fraction = fraction + (*chaine - '0') / diviseur;
                diviseur *= 10;
            }
        } 
		else 
		{
            err(1,"the value is not a double: %c\n",*chaine);
        }
        chaine++;
    }

    return signe * (resultat + fraction);
}
