#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "DataPoint.h"

double sigmoid(double x);
double dsigmoid(double x);
double init_weights();

#endif
