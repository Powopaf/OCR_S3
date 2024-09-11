#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <stdio.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
	int Safe;
} DataPoint;

void NewDataPoint(DataPoint *p, double x, double y);
int Safe(DataPoint *p);
#endif
