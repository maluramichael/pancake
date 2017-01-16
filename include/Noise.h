
#ifndef __PANCAKE__NOISE__
#define __PANCAKE__NOISE__

#include <vector>

namespace Pancake {

class Noise {
private:
  std::vector<int> p;

public:
  Noise(unsigned int seed);
  Noise();
  double noise(double x, double y, double z);
  double fade(double t);
  double lerp(double t, double a, double b);
  double grad(int hash, double x, double y, double z);
};
}

#endif