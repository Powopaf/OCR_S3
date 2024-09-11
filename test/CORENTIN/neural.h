#pragma once
#include <stdio.h>
#include "DataPoint.h"
#include <stdlib.h>

extern DataPoint *Sample;
extern int SampleSize;

extern double weight_1_1, weight_2_1;
extern double weight_1_2, weight_2_2;

int init();
int Classify(double input1, double input2);
