#include "neural.h"
#include <time.h>

DataPoint *Sample = NULL;
int SampleSize = 0;

// Fonction pour générer un nombre aléatoire de type double dans l'intervalle [min, max]
double generateRandomDouble(double min, double max) {
    // Générer un nombre aléatoire entier entre 0 et RAND_MAX
    double random = (double)rand() / RAND_MAX;
    
    // Adapter le nombre aléatoire à l'intervalle [min, max]
    return min + random * (max - min);
}


int init()
{
	srand((unsigned int)time(NULL));
	double min = 0.0;
    double max = 8.0;

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
