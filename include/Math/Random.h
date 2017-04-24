//
// Created by Michael Malura on 24/04/17.
//

#ifndef PANCAKE_RANDOM_H
#define PANCAKE_RANDOM_H

#include <cstdlib>
#include <ctime>
#include <math.h>
#include <random>

namespace Pancake {
    namespace Math {
        class Randomizer {
        private:
            std::random_device rd;
            std::mt19937 mt;

        public:
            Randomizer();

            int random(int min, int max);

            float random(float min, float max);

        };

    }
}

#endif //PANCAKE_RANDOM_H
