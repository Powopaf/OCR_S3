#include "DataPoint.h"

void NewDataPoint(DataPoint *p, double x, double y)
{
	p->x = x;
	p->y = y;
	p->pos[0] = x;
	p->pos[1] = y;
	Safe(p);
}

void Safe(DataPoint *p)
{
	double X = p->x/10.0;
	double Y = p->y;

	double f = -0.1*pow(X,4) - 0.1*pow(X,3) + pow(X,2) + 2;

	if(Y<f*10.0)
	{
		p->Safe[0] = 1.0;
		p->Safe[1] = 0.0;
	}
	else
	{
		p->Safe[0] = 0.0;
		p->Safe[1] = 1.0;
	}
}
