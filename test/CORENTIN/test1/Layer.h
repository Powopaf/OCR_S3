#pragma once

#include <stdio.h>
#include <math.h>

typedef struct
{
    int nbNodesIn, nbNodesOut;
    double **weights;
    double *biases;
} Layer;

void NewLayer(Layer *l, int nbNodesIn, int nbNodesOut);
void CalculateOutputs(Layer l, double *weightedInputs, double *inputs);
