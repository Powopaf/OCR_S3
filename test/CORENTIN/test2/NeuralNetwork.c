#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double init_weights()
{
	return ((double)rand()) / ((double)RAND_MAX);
}

double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double derivative_sigmoid(double x)
{
	return x * (1 - x);
}

#define numInputs 2
#define numHiddenNodes 2
#define num Outputs 1
#define numTrainingSets 4

int main()
{
	const double LearningRate = 0.1;

	double hiddenLayer[numHiidenNodes];
	double outputLayer[numOutputs];

	double hiddenLayerBias[numHiddenNodes];
	double outputLayerBias[numOutputs];

	double hiddenWeights[numInputs][numHiddenNodes];
	double outputWeights[numHiddenNodes][numIutputs];
	

	double training_inputs[numTraigningSets][numInputs] = { {0.0,0.0},
															{1.0,0.0},
															{0.0,1.0}
															{1.0,1.0}};

	double training_inputs[numTraigningSets][numInputs] = { {0.0,0.0},
                                                            {1.0,0.0},
                                                            {0.0,1.0}
															{1.0,1.0}};

	for(int i = 0; i<numInputs; i++)
	{
		for(int j = 0; j<numHiddenNodes; j++)
		{
			hiddenWeights[i][j] = init_weights();
		}
	}

	for(int i = 0; i<numOutputs; i++)
    {
        outputsLayerBias[i] = init_weights();
    }

	int trainingSetOrder[] = {0,1,2,3,};
	int numberOfEpochs = 10000;
	
	//train

	for(int epoch = 0; epoch<numberOfEpochs; epoch++)
	{
		
	}


