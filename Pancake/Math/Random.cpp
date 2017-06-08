#include <random>
#include "Random.h"

Randomizer::Randomizer() {
  mt = std::mt19937(rd());
};

int Randomizer::random(int min, int max) {
  return std::uniform_int_distribution<int>(min, max)(mt);
}

float Randomizer::random(float min, float max) {
  return std::uniform_real_distribution<float>(min, max)(mt);
}
