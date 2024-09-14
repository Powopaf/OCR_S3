#include "../NeuralNetwork.h"

#define nbTrainingSets 100
#define nbOfEpochs 10000


void compute(double InputsLayer[], double outputLayer[])
{

	int nbInputs;
	int nbHiddenNodes;
	int nbOutputs;

	//variable
	double LearningRate;

    double *hiddenLayerBias;
    double *outputLayerBias;

    double **hiddenWeights;
    double **outputWeights;

	LoadData("data.txt",&hiddenLayerBias, &outputLayerBias, &hiddenWeights, &outputWeights, &nbInputs, &nbHiddenNodes, &nbOutputs, &LearningRate);

	double hiddenLayer[nbHiddenNodes];

	//final 
	printf("\n");

	printf("Final Hidden Weights:\n");
	for(int i = 0; i<nbHiddenNodes; i++)
	{
		for(int j = 0; j<nbInputs; j++)
		{
			printf("%f ", hiddenWeights[j][i]);
		}
		printf("\n");
	}

	printf("Final Output Weights:\n");
    for(int i = 0; i<nbOutputs; i++)
    {
        for(int j = 0; j<nbHiddenNodes; j++)
        {
            printf("%f ", outputWeights[j][i]);
        }
        printf("\n");
    }


	printf("Final Hidden Biases: ");
	for(int i = 0; i<nbHiddenNodes; i++)
		printf("%f ", hiddenLayerBias[i]);
	printf("\n");

	printf("Final Output Biases: ");
    for(int i = 0; i<nbOutputs; i++)
        printf("%f ", outputLayerBias[i]);
	printf("\n");
	
	//comute hidden layer activation
    for(int j = 0; j<nbHiddenNodes; j++)
    {
        double activation = hiddenLayerBias[j];
        for(int k = 0; k<nbInputs; k++)
        {
            activation += InputsLayer[k] * hiddenWeights[k][j];
        }

        hiddenLayer[j] = sigmoid(activation);
    }

	//comute output layer activation
    for(int j = 0; j<nbOutputs; j++)
    {
        double activation = outputLayerBias[j];
        for(int k = 0; k<nbHiddenNodes; k++)
        {
            activation += hiddenLayer[k] * outputWeights[k][j];
        }

        outputLayer[j] = sigmoid(activation);

    }
	
}

int main()
{

	DataPoint p;
	double x = init_weights();
	double y = init_weights();
	NewDataPoint(&p,x,y);
	double output[2];
	compute(p.pos,output);
	printf("Output: %f,%f\n",output[0],output[1]);
	printf("Expected: %f,%f\n",p.Safe[0],p.Safe[1]);
	return 0;
}




