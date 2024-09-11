#include "neural.h"
#include <time.h>

Layer* Layers = NULL;
int LayersSize = 0;

DataPoint *Sample = NULL;
int SampleSize = 0;

//lib
double generateRandomDouble(double min, double max) {
    // Générer un nombre aléatoire entier entre 0 et RAND_MAX
    double random = (double)rand() / RAND_MAX;
    
    // Adapter le nombre aléatoire à l'intervalle [min, max]
    return min + random * (max - min);
}
int IndexOfMaxValue(double inputs[], int size)
{
    if (size <= 0) {
        return -1;  // Retourne -1 si la taille du tableau est invalide
    }

    int maxIndex = 0;
    double maxValue = inputs[0];

    for (int i = 1; i < size; i++) {
        if (inputs[i] > maxValue) {
            maxValue = inputs[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}


void Layers_CalculateOutputs(double inputs[])
{
	for(int i = 0; i<LayersSize; i++)
	{
		CalculateOutputs(Layers[i],&inputs,&inputs);
	}
}

int Classify(double inputs[])
{
	int outputsSize = 2;// a opti
	double outputs[outputsSize];
	Layers_CalculateOutputs(outputs);
	return IndexOfMaxValue(outputs,outputsSize);
}



//init
void initNeuralNetwork(int p[], int size)
{
	LayersSize = size-1;
	Layers = (Layer *)malloc(LayersSize*sizeof(Layer));
	for(int i = 0; i<LayersSize; i++)
	{
		Layer l;
		NewLayer(&l,p[i], p[i+1]);
		Layers[i] = l;
	}
}

int init()
{
	//init DataPoint
	srand((unsigned int)time(NULL));
	double min = 0.0;
    double max = 950.0;

	size_t nb = 250;
	SampleSize = (int)nb;
	Sample = (DataPoint *)malloc(SampleSize*sizeof(DataPoint));

	for(size_t i = 0; i<nb; i++)
	{
		DataPoint P;
		NewDataPoint(&P,generateRandomDouble(min, max),generateRandomDouble(min, max));
		Sample[i] = P;
	}

	return 0;
}

