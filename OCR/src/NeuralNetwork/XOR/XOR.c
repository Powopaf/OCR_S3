#include "../NeuralNetwork.h"

void compute(double InputsLayer[], double outputLayer[]) {
    int nbInputs, nbHiddenNodes, nbOutputs;
    double LearningRate;

    double *hiddenLayerBias;
    double *outputLayerBias;
    double **hiddenWeights;
    double **outputWeights;

    LoadData("data.txt", &hiddenLayerBias, &outputLayerBias, &hiddenWeights, &outputWeights, 
             &nbInputs, &nbHiddenNodes, &nbOutputs, &LearningRate);

    double hiddenLayer[nbHiddenNodes];

    // Final weights and biases output
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
    for (int i = 0; i < nbHiddenNodes; i++) printf("%f ", hiddenLayerBias[i]);
    printf("\n");

    printf("Final Output Biases: ");
    for (int i = 0; i < nbOutputs; i++) printf("%f ", outputLayerBias[i]);
    printf("\n");

    // Compute hidden layer activation
    for (int j = 0; j < nbHiddenNodes; j++) {
        double activation = hiddenLayerBias[j];
        for (int k = 0; k < nbInputs; k++) {
            activation += InputsLayer[k] * hiddenWeights[k][j];
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

    FreeMatrix(hiddenWeights, nbInputs);
    FreeMatrix(outputWeights, nbHiddenNodes);
    free(hiddenLayerBias);
    free(outputLayerBias);
}

int main() {
    double input[2] = {1.0, 0.0};
    printf("Input: %f, %f\n", input[0], input[1]);

    double output[1];
    compute(input, output);
    printf("Output: %f\n", output[0]);

    return 0;

}

