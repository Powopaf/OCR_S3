#include "DataPoint.h"

void NewDataPoint(DataPoint *p, double x, double y)
{
	p->x = x;
	p->y = y;
	p->Safe = Safe(p);
}

int Safe(DataPoint *p)
{
	double X = p->x;
	double Y = p->y;

	double X1 = pow(X,4);
	double X2 = pow(X,3);
	double X3 = pow(X,2);

	double f = -0.1*X1 - 0.1*X2 + X3 + 2;
	if(Y<f)
		return 1;
	else
		return 0;
}
