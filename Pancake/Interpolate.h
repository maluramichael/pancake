//
// Created by Michael Malura on 26/04/17.
//

#ifndef PANCAKE_LERP_H
#define PANCAKE_LERP_H

#include <math.h>

namespace Pancake {
    namespace Math {

        float interpolate(float from, float to, float t);

        float interpolateCosine(float from, float to, float t);

        float interpolateCube(float y0, float y1, float y2, float y3, float mu);

        float interpolateHermite(
                double y0, double y1,
                double y2, double y3,
                double mu,
                double tension,
                double bias);
    }
}

#endif //PANCAKE_LERP_H
