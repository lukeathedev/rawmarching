#include "math.h"

double _sqrt(double x, double precision) {
  double start = 0, end = x, mid = 0;

  while ((end - start) >= precision) {
    mid = (start + end) / 2;

    if (mid * mid < x) {
      start = mid;
    }

    if (mid * mid >= x) {
      end = mid;
    }
  }

  return mid;
}

int imin(int a, int b) {
  return a <= b ? a : b;
}
float fmin(float a, float b) {
  return a <= b ? a : b;
}

int imax(int a, int b) {
  return a >= b ? a : b;
}
float fmax(float a, float b) {
  return a >= b ? a : b;
}

float clamp(float a, float min, float max) {
  if (a > max) return max;
  if (a < min) return min;
  return a;
}
