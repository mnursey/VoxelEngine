// Adapted into C++ from Simlex Noise Demystified by Stefan Gustavson

#include "SimplexNoise.h"

int SimplexNoise::fastFloor(double x)
{
	return x > 0 ? (int)x : (int)x - 1;
}

double SimplexNoise::dot(const int g[], double x, double y)
{
	return g[0] * x + g[1] * y;
}

double SimplexNoise::dot(int g[], double x, double y, double z)
{
	return g[0] * x + g[1] * y + g[2] * z;
}

double SimplexNoise::dot(int g[], double x, double y, double z, double w)
{
	return g[0] * x + g[1] * y + g[2] * z + g[3] * w;
}

double SimplexNoise::noise(double xin, double yin)
{
	// Noise contributions from the three corners
	double n0, n1, n2;

	// Skew the input space to determine which simplex cell we're in
	double F2 = 0.5 * (std::sqrt(3.0) - 1.0);
	double s = (xin + yin) * F2;	// Hairy factor for 2D
	int i = fastFloor(xin + s);
	int j = fastFloor(yin + s);

	double G2 = (3.0 - std::sqrt(3.0)) / 6.0;
	double t = (i + j) * G2;
	double X0 = i - t;	// Unskew the cell origin back to (x, y) space
	double Y0 = j - t;
	double x0 = xin - X0;	// The x, y distances from the cell origin
	double y0 = yin - Y0;

	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1;		// Offsets for second (middle) corner of simlex in (i, j) coords
	if (x0 > y0)	// Lower triangle, XY order: (0, 0) -> (1, 0) -> (1, 1)
	{
		i1 = 1;
		j1 = 0;
	}
	else			// Upper triangle, YX order: (0, 0) -> (0, 1) -> (1, 1)
	{
		i1 = 0;
		j1 = 1;
	}

	// A step of (1, 0) in (i, j) means a step of (1-c, -c) in (x, y) and
	// a step of (0, 1) in (i, j) means a step of (-c, 1-c) in (x, y) where
	// c = (c - sqrt(3)) / 6

	double x1 = x0 - i1 + G2;	// Offsets for middle corner in (x, y) unskewed coords
	double y1 = y0 - j1 + G2;
	double x2 = x0 - 1.0 + 2.0 * G2;	// Offsets for last corner in (x, y) unskewed coords
	double y2 = y0 - 1.0 + 2.0 * G2;

	// Work out the hashed gradient indicies of the three simplex corners
	int ii = i & 255;
	int jj = j & 255;
	int gi0 = perm[ii + perm[jj]] % 12;
	int gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
	int gi2 = perm[ii + 1 + perm[jj + 1]] % 12;

	// Calculate the contribution from the three corners
	double t0 = 0.5 - (x0 * x0) - (y0 * y0);
	if (t0 < 0)
	{
		n0 = 0.0;
	}
	else 
	{
		t0 *= t0;
		n0 = t0 * t0 * dot(grad3[gi0], x0, y0);		// (x, y) of grad 3 used for 2D gradient
	}

	double t1 = 0.5 - (x1 * x1)- (y1 * y1);
	if (t1 < 0)
	{
		n1 = 0.0;
	}
	else 
	{
		t1 *= t1;
		n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
	}

	double t2 = 0.5 - (x2 * x2) - (y2 * y2);
	if (t2 < 0)
	{
		n2 = 0.0;
	}
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
	}

	// Add contributions from each corner to get the final noise value.
	// The result is scaled to return values in the interval [-1, 1].
	return 70.0 * (n0 + n1 + n2);
}

double SimplexNoise::noise(double xin, double yin, double zin)
{
	return 0.0;
}

double SimplexNoise::noise(double xin, double yin, double zin, double win)
{
	return 0.0;
}
