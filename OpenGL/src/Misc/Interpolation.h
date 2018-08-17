#pragma once

void interpolate(double x1, double x2, double t, double out[]);

void interpolate(double x1, double x2, double y1,double y2,  double t, double out[]);

void interpolate(double x1, double x2, double y1, double y2, double z1, double z2, double t, double out[]);

double binterpolate(double a, double b, double c, double d, double x, double y);