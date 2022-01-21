#ifndef STD_MATH_H
#define STD_MATH_H

#define MATH_PRECISION 0.001

#define sqrt(x) _sqrt(x, MATH_PRECISION)
double _sqrt(double x, double precision);

int imin(int a, int b);
float fmin(float a, float b);

int imax(int a, int b);
float fmax(float a, float b);

float clamp(float a, float min, float max);

#endif
