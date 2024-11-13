#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <time.h>

// Neural network functions
double sigmoid(double x);
double dsigmoid(double x);
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
void WriteData(char filename[], double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights, int nbInputs, int nbHiddenNodes, int nbOutputs, double LearningRate, int epoch);

char*** MallocDataSet();
void FreeDataSet(char*** arr);
char*** LoadDataSet(char*** arr);
double* LetterToArray(char letter);
char ArrayToLetter(double* arr);
double** LoadExeptedDataSet();
double* GetExeptedDataSet(double** ExeptedDataSet, char Letter);
char* LoadImgData(SDL_Surface* surface);

double init_weights();
void InitTrainning(int nbInputs, int nbHiddenNodes ,int nbOutputs , double*** hiddenWeights, double** hiddenLayerBias ,double*** outputWeights, double** outputLayerBias);
void shuffle(int** mat, int sizex, int sizey);