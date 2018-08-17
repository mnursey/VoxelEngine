#include "Interpolation.h"

void interpolate(double x1, double x2, double t, double out[])
{
	out[0] = (x2 - x1) * t + x1;
}

void interpolate(double x1, double x2, double y1, double y2, double t, double out[])
{
	out[0] = (x2 - x1) * t + x1;
	out[1] = (y2 - y1) * t + y1;
}

void interpolate(double x1, double x2, double y1, double y2, double z1, double z2, double t, double out[])
{
	out[0] = (x2 - x1) * t + x1;
	out[1] = (y2 - y1) * t + y1;
	out[2] = (z2 - z1) * t + z1;
}

double binterpolate(double a, double b, double c, double d, double x, double y)
{
	// 0 <= x <= 1, 0 <= y <= 1
	return (c) * (1 - x) * (1 - y) + (d) * (x)  * (1 - y) + (a) * (1 - x) * (y) + (b) * (x) * (y);
}