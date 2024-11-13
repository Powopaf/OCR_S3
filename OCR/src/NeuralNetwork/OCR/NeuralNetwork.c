#include "../NeuralNetwork.h"

#define nbTrainingSets 1000
#define nbOfEpochs 10


void compute(char* InputsLayer, double** outputLayer)
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

	FreeMatrix(hiddenWeights, nbInputs);
    FreeMatrix(outputWeights, nbHiddenNodes);
    free(hiddenLayerBias);
    free(outputLayerBias);
	
}

char LetterRecognition(SDL_Surface* surface)
{
	double* output = malloc(26*sizeof(double));

	char* res = LoadImgData(surface);

	compute(res,&output);
	free(res);

	char Letter = ArrayToLetter(output);

	//print res
	printf("Output: %c\n",Letter);
	for(int i = 0; i<26;i++)
	{
		printf("%c:%.3f|",(char)(i+'A'),output[i]);
	}
	printf("\n");
	//---

	free(output);
	
	return Letter;
}

int main(int argc, char** argv)
{
	SDL_Surface* surface = SDL_LoadBMP(argv[1]);
	LetterRecognition(surface);
	SDL_FreeSurface(surface);
}



