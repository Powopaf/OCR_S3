#include "../NeuralNetwork.h"

#define nbInputs 2
#define nbHiddenNodes 3
#define nbOutputs 1
#define nbTrainingSets 4
#define nbOfEpochs 10000

void train() {
    // Variable initialization
    const double LearningRate = 0.1f;

    double hiddenLayer[nbHiddenNodes];
    double outputLayer[nbOutputs];

    double *hiddenLayerBias;
    MallocArray(&hiddenLayerBias, nbHiddenNodes);
    double *outputLayerBias;
    MallocArray(&outputLayerBias, nbOutputs);

    double **hiddenWeights;
    MallocMatrix(&hiddenWeights, nbInputs, nbHiddenNodes);
    double **outputWeights;
    MallocMatrix(&outputWeights, nbHiddenNodes, nbOutputs);

    double totalError = 0.0;

    // Generate training sets
    double TrainingSets[nbTrainingSets][2] = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0},
    };

    double OutputsSets[nbTrainingSets] = {0.0, 1.0, 1.0, 0.0};

    // Initialize all weights and biases to random values
    for (int i = 0; i < nbInputs; i++) {
        for (int j = 0; j < nbHiddenNodes; j++) {
            hiddenWeights[i][j] = init_weights();
        }
    }

    for (int i = 0; i < nbHiddenNodes; i++) {
        hiddenLayerBias[i] = init_weights();
    }

    for (int i = 0; i < nbHiddenNodes; i++) {
        for (int j = 0; j < nbOutputs; j++) {
            outputWeights[i][j] = init_weights();
        }
    }

    for (int i = 0; i < nbOutputs; i++) {
        outputLayerBias[i] = init_weights();
    }

    // Training phase
    for (int epoch = 0; epoch < nbOfEpochs; epoch++) {
        totalError = 0.0;

        for (int x = 0; x < nbTrainingSets; x++) {
            // Forward pass: compute hidden layer activation
            for (int j = 0; j < nbHiddenNodes; j++) {
                double activation = hiddenLayerBias[j];
                for (int k = 0; k < nbInputs; k++) {
                    activation += TrainingSets[x][k] * hiddenWeights[k][j];
                }
                hiddenLayer[j] = sigmoid(activation);
            }

            // Compute output layer activation
            for (int j = 0; j < nbOutputs; j++) {
                double activation = outputLayerBias[j];
                for (int k = 0; k < nbHiddenNodes; k++) {
                    activation += hiddenLayer[k] * outputWeights[k][j];
                }
                outputLayer[j] = sigmoid(activation);
            }

            printf("Input: %f, %f  Output: %f  Expected: %f\n", TrainingSets[x][0], TrainingSets[x][1], outputLayer[0], OutputsSets[x]);

            // Backpropagation phase
            double deltaOutput[nbOutputs];

            // Compute change in output weights
            for (int j = 0; j < nbOutputs; j++) {
                double error = OutputsSets[x] - outputLayer[j];
                totalError += error * error;
                deltaOutput[j] = error * dsigmoid(outputLayer[j]);
            }

            double deltaHidden[nbHiddenNodes];

            // Compute change in hidden weights
            for (int j = 0; j < nbHiddenNodes; j++) {
                double error = 0.0;
                for (int k = 0; k < nbOutputs; k++) {
                    error += deltaOutput[k] * outputWeights[j][k];
                }
                deltaHidden[j] = error * dsigmoid(hiddenLayer[j]);
            }

            // Apply changes to output weights
            for (int j = 0; j < nbOutputs; j++) {
                outputLayerBias[j] += deltaOutput[j] * LearningRate;
                for (int k = 0; k < nbHiddenNodes; k++) {
                    outputWeights[k][j] += hiddenLayer[k] * deltaOutput[j] * LearningRate;
                }
            }

            // Apply changes to hidden weights
            for (int j = 0; j < nbHiddenNodes; j++) {
                hiddenLayerBias[j] += deltaHidden[j] * LearningRate;
                for (int k = 0; k < nbInputs; k++) {
                    hiddenWeights[k][j] += TrainingSets[x][k] * deltaHidden[j] * LearningRate;
                }
            }
        }
    }

    WriteData("data.txt", hiddenLayerBias, outputLayerBias, hiddenWeights, outputWeights, nbInputs, nbHiddenNodes, nbOutputs, LearningRate);

    // Display final weights and biases
    printf("\nFinal Hidden Weights:\n");
    for (int i = 0; i < nbHiddenNodes; i++) {
        for (int j = 0; j < nbInputs; j++) {
            printf("%f ", hiddenWeights[j][i]);
        }
        printf("\n");
    }

    printf("Final Output Weights:\n");
    for (int i = 0; i < nbOutputs; i++) {
        for (int j = 0; j < nbHiddenNodes; j++) {
            printf("%f ", outputWeights[j][i]);
        }
        printf("\n");
    }

    printf("Final Hidden Biases: ");
    for (int i = 0; i < nbHiddenNodes; i++) {
        printf("%f ", hiddenLayerBias[i]);
    }
    printf("\n");

    printf("Final Output Biases: ");
    for (int i = 0; i < nbOutputs; i++) {
        printf("%f ", outputLayerBias[i]);
    }
    printf("\n");

    double meanSquaredError = totalError / (nbTrainingSets * nbOutputs);
    printf("Final MSE: %f\n", meanSquaredError);

    // Free allocated memory
    FreeMatrix(hiddenWeights, nbInputs);
    FreeMatrix(outputWeights, nbHiddenNodes);
    free(hiddenLayerBias);
    free(outputLayerBias);
}

int main() {
    train();
    return 0;
}

