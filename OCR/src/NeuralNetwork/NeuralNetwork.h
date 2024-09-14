#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

#include "DataPoint.h"

double sigmoid(double x);
double dsigmoid(double x);
double init_weights();

int ReadInt(const char *chaine);
double ReadDouble(const char *chaine); 
#endif
