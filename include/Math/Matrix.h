//
// Created by Michael Malura on 28/04/17.
//

#ifndef PANCAKE_MATRIX_H
#define PANCAKE_MATRIX_H

#include <memory>
#include <ostream>
#include <iomanip>
#include <iostream>

#include "Math.h"
#include "Vector2.h"

namespace Pancake {
    namespace Math {

        class Matrix {
        public:
            Matrix();

            ~Matrix();

            void loadIdentity();

            static void translate(Pancake::Math::Matrix& m, Pancake::Math::Vector2 v);

            static void scale(Pancake::Math::Matrix& m, Pancake::Math::Vector2 v);

            static void rotateX(Pancake::Math::Matrix& m, float t);

            static void rotateY(Pancake::Math::Matrix& m, float t);

            static void rotateZ(Pancake::Math::Matrix& m, float t);

//            friend std::ostream& operator<<(std::ostream& stream, const Matrix& m);

            Matrix operator*(const Matrix& o);

            float data[16] = {0};
            float* firstRow[4];
            float* secondRow[4];
            float* thirdRow[4];
            float* fourthRow[4];
            float* firstColumn[4];
            float* secondColumn[4];
            float* thirdColumn[4];
            float* fourthColumn[4];

        private:
            float combineRowAndColumn(float* row, float* column);
        };
    }
}

#endif //PANCAKE_MATRIX_H