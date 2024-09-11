#include "neural.h"
#include <time.h>

DataPoint *Sample = NULL;
int SampleSize = 0;

double weight_1_1, weight_2_1;
double weight_1_2, weight_2_2;

double bias_1, bias_2;
// Fonction pour générer un nombre aléatoire de type double dans l'intervalle [min, max]
double generateRandomDouble(double min, double max) {
    // Générer un nombre aléatoire entier entre 0 et RAND_MAX
    double random = (double)rand() / RAND_MAX;
    
    // Adapter le nombre aléatoire à l'intervalle [min, max]
    return min + random * (max - min);
}


int init()
{
	weight_1_1 = 5.0;
	weight_1_2 = 1.0;
	weight_2_1 = 1.0;
	weight_2_2 = 4.0;

	bias_1 = 1.0;
	bias_2 = 1.0;


	srand((unsigned int)time(NULL));
	double min = 0.0;
    double max = 950.0;

	size_t nb = 250;
	SampleSize = 250;
	Sample = (DataPoint *)malloc(SampleSize*sizeof(DataPoint));
	for(size_t i = 0; i<nb; i++)
	{
		DataPoint P;
		NewDataPoint(&P,generateRandomDouble(min, max),generateRandomDouble(min, max));
		Sample[i] = P;
	}
	return 0;
}

int Classify(double input1, double input2)
{
	double output1 = input1 * weight_1_1 + input2 * weight_2_1 + bias_1;
	double output2 = input1 * weight_1_2 + input2 * weight_2_2 + bias_2;

	return (output1>output2) ? 0 : 1;
}


