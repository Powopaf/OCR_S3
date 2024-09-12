#include "../../Hfile/NeuralNetwork.h"

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
