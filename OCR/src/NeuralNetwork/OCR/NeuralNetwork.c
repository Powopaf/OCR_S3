#include "../NeuralNetwork.h"

#define nbTrainingSets 1000
#define nbOfEpochs 10


void compute(char* InputsLayer, double** outputLayer,int nbInputs,int nbHiddenNodes,int nbOutputs,double LearningRate,double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights)
{

    /*
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
    */
	double hiddenLayer[nbHiddenNodes];
    if(LearningRate==-42.0)
    {
        return;
    }

	
	//comute hidden layer activation
    for(int j = 0; j<nbHiddenNodes; j++)
    {
        double activation = hiddenLayerBias[j];
        for(int k = 0; k<nbInputs; k++)
        {
            activation += (double)InputsLayer[k] * hiddenWeights[k][j];
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

        (*outputLayer)[j] = sigmoid(activation);

    }

    /*
	FreeMatrix(hiddenWeights, nbInputs);
    FreeMatrix(outputWeights, nbHiddenNodes);
    free(hiddenLayerBias);
    free(outputLayerBias);
    */
	
}

char LetterRecognition(SDL_Surface* surface,int nbInputs,int nbHiddenNodes,int nbOutputs,double LearningRate,double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights)
{
	double* output = malloc(26*sizeof(double));

	char* res = LoadImgData(surface);

	compute(res,&output,nbInputs,nbHiddenNodes,nbOutputs,LearningRate,hiddenLayerBias,outputLayerBias,hiddenWeights,outputWeights);
	free(res);

	char Letter = ArrayToLetter(output);
    /*
	//print res
	printf("Output: %c\n",Letter);
	for(int i = 0; i<26;i++)
	{
		printf("%c:%.3f|",(char)(i+'A'),output[i]);
	}
	printf("\n");
	//---
    */
	free(output);
	
	return Letter;
}