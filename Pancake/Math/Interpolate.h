#ifndef PANCAKE_LERP
#define PANCAKE_LERP

#include <math.h>

float interpolate(float from, float to, float t);

float interpolateCosine(float from, float to, float t);

float interpolateCube(float y0, float y1, float y2, float y3, float mu);

float interpolateHermite(
  double y0, double y1,
  double y2, double y3,
  double mu,
  double tension,
  double bias);

#endif
