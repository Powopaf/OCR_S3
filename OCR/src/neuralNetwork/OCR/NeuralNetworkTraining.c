#include "../NeuralNetwork.h"

#define nbInputs 2
#define nbHiddenNodes 3
#define nbOutputs 2
#define nbTrainingSets 100
#define nbOfEpochs 10000

void train()
{
	//variable
	const double LearningRate = 0.1f;

    double hiddenLayer[nbHiddenNodes];
    double outputLayer[nbOutputs];

    double *hiddenLayerBias;
	MallocArray(&hiddenLayerBias,nbHiddenNodes);
    double *outputLayerBias;
	MallocArray(&outputLayerBias,nbOutputs);

    double **hiddenWeights;
	MallocMatrix(&hiddenWeights,nbInputs,nbHiddenNodes);
    double **outputWeights;
	MallocMatrix(&outputWeights,nbHiddenNodes,nbOutputs);
	
	double totalError = 0.0;

	//generate training sets
	DataPoint TrainingSets[nbTrainingSets];
	for(int i = 0; i<nbTrainingSets; i++)
	{
		DataPoint p;
		double x = init_weights();
		double y = init_weights();
		NewDataPoint(&p,x,y);
		TrainingSets[i] = p;

		//printf("Pos: %f,%f Safe:[%i,%i]\n",x,y,p.Safe[0],p.Safe[1]);
	}
	
	//set all weights and bias to random value
	for(int i = 0; i<nbInputs; i++)
    {
        for(int j = 0; j<nbHiddenNodes; j++)
        {
            hiddenWeights[i][j] = init_weights();
        }
    }

    for(int i = 0; i<nbOutputs; i++)
    {
        outputLayerBias[i] = init_weights();
    }

	//training
	for(int epoch = 0; epoch<nbOfEpochs; epoch++)
    {
		totalError = 0.0;

		for (int x = 0; x<nbTrainingSets; x++)
		{
			DataPoint p = TrainingSets[x];
			
			//forward pass

			//comute hidden layer activation
			for(int j = 0; j<nbHiddenNodes; j++)
			{
				double activation = hiddenLayerBias[j];
				for(int k = 0; k<nbInputs; k++)
				{
					activation += p.pos[k] * hiddenWeights[k][j];
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

			printf("Input: %f,%f  Output: %f,%f  Expected: %f,%f\n",p.x,p.y,outputLayer[0],outputLayer[1],p.Safe[0],p.Safe[1]);

			// Backprop

			//compute change in output weights

			double deltaOutput[nbOutputs];

			for(int j = 0; j<nbOutputs; j++)
			{
				double error = (p.Safe[j] - outputLayer[j]);
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
                    hiddenWeights[k][j] += p.pos[k] * deltaHidden[j] * LearningRate;
                }
            }

		}

    }
	

	WriteData("data.txt",hiddenLayerBias,outputLayerBias,hiddenWeights,outputWeights,nbInputs,nbHiddenNodes,nbOutputs,LearningRate);

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

	double meanSquaredError = totalError / (nbTrainingSets * nbOutputs);
    printf("Final MSE: %f\n", meanSquaredError);

}


int main()
{
	train();
	return 0;
}





