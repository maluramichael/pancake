//
// Created by Michael Malura on 24/04/17.
//

#include <random>
#include "Random.h"

Pancake::Math::Randomizer::Randomizer() {
    mt = std::mt19937(rd());
};

int Pancake::Math::Randomizer::random(int min, int max) {
    return std::uniform_int_distribution<int>(min, max)(mt);
}

float Pancake::Math::Randomizer::random(float min, float max) {
    return std::uniform_real_distribution<float>(min, max)(mt);
}
