#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <stdio.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
	double pos[2];
	double Safe[2];
} DataPoint;

void NewDataPoint(DataPoint *p, double x, double y);
void Safe(DataPoint *p);

#endif
