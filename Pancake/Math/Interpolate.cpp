#include "Interpolate.h"

float interpolate(float from, float to, float t) {
  return (from * (1 - t) + to * t);
}

float interpolateCosine(float from, float to, float t) {
  double mu2;
  
  mu2 = (1 - cos(t * M_PI)) / 2;
  return (float) (from * (1 - mu2) + to * mu2);
}

float interpolateCube(float y0, float y1, float y2, float y3, float mu) {
  double a0, a1, a2, a3, mu2;
  
  mu2 = mu * mu;
  a0 = y3 - y2 - y0 + y1;
  a1 = y0 - y1 - a0;
  a2 = y2 - y0;
  a3 = y1;
  
  return (float) (a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);
}

float interpolateHermite(double y0, double y1, double y2, double y3, double mu, double tension, double bias) {
  double m0, m1, mu2, mu3;
  double a0, a1, a2, a3;
  
  mu2 = mu * mu;
  mu3 = mu2 * mu;
  m0 = (y1 - y0) * (1 + bias) * (1 - tension) / 2;
  m0 += (y2 - y1) * (1 - bias) * (1 - tension) / 2;
  m1 = (y2 - y1) * (1 + bias) * (1 - tension) / 2;
  m1 += (y3 - y2) * (1 - bias) * (1 - tension) / 2;
  a0 = 2 * mu3 - 3 * mu2 + 1;
  a1 = mu3 - 2 * mu2 + mu;
  a2 = mu3 - mu2;
  a3 = -2 * mu3 + 3 * mu2;
  
  return (float) (a0 * y1 + a1 * m0 + a2 * m1 + a3 * y2);
}
