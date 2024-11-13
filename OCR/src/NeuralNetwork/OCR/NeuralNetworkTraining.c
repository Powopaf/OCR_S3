#include "../NeuralNetwork.h"

#define nbInputs 784
#define nbHiddenNodes 785
#define nbOutputs 26
#define nbTrainingSets 1000

void train(int nbOfEpochs)
{
	//variable
	const double LearningRate = 0.1f;

    double hiddenLayer[nbHiddenNodes];
    double* outputLayer = malloc(nbOutputs*sizeof(double));

    double *hiddenLayerBias;
	MallocArray(&hiddenLayerBias,nbHiddenNodes);
    double *outputLayerBias;
	MallocArray(&outputLayerBias,nbOutputs);

    double **hiddenWeights;
	MallocMatrix(&hiddenWeights,nbInputs,nbHiddenNodes);
    double **outputWeights;
	MallocMatrix(&outputWeights,nbHiddenNodes,nbOutputs);
	
	double totalError = 0.0;

	//Load DataSet
	char*** DataSet = MallocDataSet();
	DataSet = LoadDataSet(DataSet);

	double** ExeptedDataSet = LoadExeptedDataSet();
	
	//set all weights and bias to random value
	InitTrainning(nbInputs,nbHiddenNodes,nbOutputs,&hiddenWeights,&hiddenLayerBias,&outputWeights,&outputLayerBias);

	//training

	clock_t debut, fin;
	debut = clock();

	int step = 0;
	int MaxStep = nbOutputs*nbTrainingSets*nbOfEpochs;
	for(int epoch = 0; epoch<nbOfEpochs; epoch++)
    {
		totalError = 0.0;
		for(int x = 0; x<nbTrainingSets; x++)
		{


			for (int l = 0; l<nbOutputs; l++)
			{
				char ActualLetter = l+'A';
				double* ExeptedData = GetExeptedDataSet(ExeptedDataSet,ActualLetter);

				char* p = DataSet[l][x];
				
				//forward pass

				//comute hidden layer activation
				for(int j = 0; j<nbHiddenNodes; j++)
				{
					double activation = hiddenLayerBias[j];
					for(int k = 0; k<nbInputs; k++)
					{
						activation += (double)p[k] * hiddenWeights[k][j];
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
				char out = ArrayToLetter(outputLayer);
				double percentage = (double)step / MaxStep * 100;
				printf("Input: %c  Output: %c:%.3f",ActualLetter,out,outputLayer[l]);
				printf(" Expected: %c	%i/%i 	%.3f%%\n",ActualLetter,step,MaxStep,percentage);

				// Backprop

				//compute change in output weights

				double deltaOutput[nbOutputs];


				for(int j = 0; j<nbOutputs; j++)
				{
					double error = (ExeptedData[j] - outputLayer[j]);
					totalError += error*error;
					deltaOutput[j] = error * dsigmoid(outputLayer[j]);
				}
				
				//compute change in hidden weights

				double deltaHidden[nbHiddenNodes];
				
				for(int j = 0; j<nbHiddenNodes; j++)
				{
					double error = 0.0f;
					for(int k = 0; k<nbOutputs; k++)
					{
						error+=deltaOutput[k] * outputWeights[j][k];
					}
					deltaHidden[j] = error * dsigmoid(hiddenLayer[j]);
				}
				
				// Apply change in output weights
				for(int j = 0; j< nbOutputs; j++)
				{
					outputLayerBias[j] += deltaOutput[j] * LearningRate;
					for(int k = 0; k<nbHiddenNodes; k++)
					{
						outputWeights[k][j] += hiddenLayer[k] * deltaOutput[j] * LearningRate;
					}
				}

				// Apply change in hidden weights
				for(int j = 0; j< nbHiddenNodes; j++)
				{
					hiddenLayerBias[j] += deltaHidden[j] * LearningRate;
					for(int k = 0; k<nbInputs; k++)
					{
						hiddenWeights[k][j] += (double)p[k] * deltaHidden[j] * LearningRate;
					}
				}

				step++;

			}
		}

    }
	
	fin = clock();
	printf("Temps d'exécution : %f secondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);

	WriteData("data.txt",hiddenLayerBias,outputLayerBias,hiddenWeights,outputWeights,nbInputs,nbHiddenNodes,nbOutputs,LearningRate);

	//final 

	double meanSquaredError = totalError / (nbTrainingSets * nbOutputs);
    printf("Final MSE: %f\n", meanSquaredError);

	// Free allocated memory
    FreeMatrix(hiddenWeights, nbInputs);
    FreeMatrix(outputWeights, nbHiddenNodes);
    free(hiddenLayerBias);
    free(outputLayerBias);

	FreeDataSet(DataSet);
	FreeMatrix(ExeptedDataSet,nbOutputs);

	free(outputLayer);



}


int main()
{
	train(200);
	return 0;
}





