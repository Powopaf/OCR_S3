#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "DataPoint.h"
#include "Layer.h"

extern Layer* Layers;
extern int LayersSize;

extern DataPoint *Sample;
extern int SampleSize;

void Layers_CalculateOutputs(double inputs[]);
int Classify(double inputs[]);
void initNeuralNetwork(int p[], int size);

int init();
