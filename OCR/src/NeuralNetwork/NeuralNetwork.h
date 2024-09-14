#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>
#include <string.h>

#include "OCR/DataPoint.h"

double sigmoid(double x);
double dsigmoid(double x);
double init_weights();

int ReadInt(char str[]);
double ReadDouble(char str[]); 

void MallocArray(double **arr,int size);
void MallocMatrix(double ***arr, int sizex, int sizey);

char** Split(char *str, int *size);

void LoadData(char filename[],double **hiddenLayerBias, double **outputLayerBias, double ***hiddenWeights, double ***outputWeights, int *nbInputs, int *nbHiddenNodes, int *nbOutputs, double *LearningRate);

void WriteData(char filename[], double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights, int nbInputs, int nbHiddenNodes, int nbOutputs, double LearningRate);

#endif
