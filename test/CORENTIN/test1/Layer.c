#include "Layer.h"
#include <stdlib.h>

void NewLayer(Layer *l, int nbNodesIn, int nbNodesOut)
{
    l->nbNodesIn = nbNodesIn;
    l->nbNodesOut = nbNodesOut;

    // Allocation pour weights
    l->weights = (double **)malloc(nbNodesOut * sizeof(double *));
    for (int i = 0; i < nbNodesOut; i++) {
        l->weights[i] = (double *)malloc(nbNodesIn * sizeof(double));
    }

    // Allocation pour biases
    l->biases = (double *)malloc(nbNodesOut * sizeof(double));

    // Initialisation des poids et biais à zéro (optionnel)
    for (int i = 0; i < nbNodesOut; i++) 
	{
        for (int j = 0; j < nbNodesIn; j++) 
		{
            l->weights[i][j] = 0.0;
        }
        l->biases[i] = 0.0;
    }
}

double ActivationFunction(double input)
{
	return 1 / (1 + exp(-input));
}

double NodeCost(double outputActivation, double expectedOutput)
{
	double error = outputActivation - expectedOutput;
	return error*error;
}

void CalculateOutputs(Layer l, double *weightedInputs, double *inputs)
{
	//double weightedInputs[numNodesOut] = {};

	for(int nodeOut = 0; nodeOut<l.nbNodesOut; nodeOut++)
	{
		double weightedInput = l.biases[nodeOut];
		for(int nodeIn = 0; nodeIn < l.nbNodesIn; nodeIn++)
		{
			weightedInput += *(inputs+nodeIn) * (*l.weights[nodeIn, nodeOut]);
		}
		*(weightedInputs + nodeOut) = ActivationFunction(weightedInput);
	}
}

