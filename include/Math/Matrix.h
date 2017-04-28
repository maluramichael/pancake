//
// Created by Michael Malura on 28/04/17.
//

#ifndef PANCAKE_MATRIX_H
#define PANCAKE_MATRIX_H

#include <memory>
#include <ostream>
#include <iomanip>
#include <iostream>

#include "Vector2.h"

namespace Pancake {
    namespace Math {
        class Matrix {
        public:
            Matrix() {
                data = new float[16];
                loadIdentity();
            }

            ~Matrix() {
                delete[] data;
            }

            void loadIdentity() {
                float d[] = {
                        1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1,
                };
                memcpy(data, d, sizeof(float) * 16);
            }

            void setTranslate(Vector2 v) {

            }

            void setScale(Vector2 v) {

            }

            void setRotation(Vector2 v) {

            }

            friend std::ostream& operator<<(std::ostream& stream, const Matrix& m);

        private:
            float* data = nullptr;
        };
    }
}

#endif //PANCAKE_MATRIX_H
