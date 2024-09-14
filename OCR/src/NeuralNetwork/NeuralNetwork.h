#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>
<<<<<<< HEAD
#include <string.h>
=======
>>>>>>> main

#include "OCR/DataPoint.h"

double sigmoid(double x);
double dsigmoid(double x);
double init_weights();

<<<<<<< HEAD
int ReadInt(char str[]);
double ReadDouble(char str[]); 

void MallocArray(double **arr,int size);
void MallocMatrix(double ***arr, int sizex, int sizey);

char** Split(char *str, int *size);

void LoadData(char filename[],double **hiddenLayerBias, double **outputLayerBias, double ***hiddenWeights, double ***outputWeights, int *nbInputs, int *nbHiddenNodes, int *nbOutputs, double *LearningRate);

void WriteData(char filename[], double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights, int nbInputs, int nbHiddenNodes, int nbOutputs, double LearningRate);

=======
int ReadInt(const char *chaine);
double ReadDouble(const char *chaine); 
>>>>>>> main
#endif
