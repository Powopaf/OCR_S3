#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <err.h>
#include <SDL2/SDL.h>

// Neural network functions
double sigmoid(double x);
double dsigmoid(double x);
double init_weights();
int ReadInt(char str[]);
double ReadDouble(char str[]);
void MallocArray(double **arr, int size);
void MallocMatrix(double ***arr, int sizex, int sizey);
void FreeMatrix(double **arr, int sizex);
char **Split(char *str, int *size);
void FreeSplitArray(char **arr, int size);
void LoadData(char filename[], double **hiddenLayerBias, double **outputLayerBias, 
              double ***hiddenWeights, double ***outputWeights, int *nbInputs, 
              int *nbHiddenNodes, int *nbOutputs, double *LearningRate);
void WriteData(char filename[], double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights, int nbInputs, int nbHiddenNodes, int nbOutputs, double LearningRate);

char*** MallocDataSet();
void FreeDataSet(char*** arr);
char*** LoadDataSet(char*** arr);