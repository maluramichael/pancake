//
// Created by Michael Malura on 10/04/17.
//

#ifndef PANCAKE_VECTOR2_H
#define PANCAKE_VECTOR2_H

#include <math.h>
#include <ostream>

namespace Pancake {
    namespace Math {

        class Vector2 {
        public:
            // Fields
            float x = 0, y = 0;

            // Generators
            static Vector2 Zero();

            static Vector2 One();

            static Vector2 Up();

            static Vector2 Down();

            static Vector2 Left();

            static Vector2 Right();

            // Constructors
            Vector2();

            Vector2(float v);

            Vector2(float x, float y);

            // Operators
            Vector2 operator+(const Vector2& o) const;

            Vector2 operator-(const Vector2& o) const;

            Vector2 operator*(const Vector2& o) const;

            Vector2 operator/(const Vector2& o) const;

            Vector2 operator+(const float& o) const;

            Vector2 operator-(const float& o) const;

            Vector2 operator*(const float& o) const;

            Vector2 operator/(const float& o) const;

            friend std::ostream& operator<<(std::ostream& stream, const Vector2& v);

            // Methods
            void move(float x, float y);

            void add(const Vector2& o);

            void subtract(const Vector2& o);

            void multiply(const Vector2& o);

            void divide(const Vector2& o);

            void add(float o);

            void subtract(float o);

            void multiply(float o);

            void divide(float o);

            void invert();

            float dot(const Vector2& o) const;

            void normalize();

            Vector2 normalized();

            double length();

            void rotate(float theta);

            float rad();

            float deg();
        };
    }
}

#endif //PANCAKE_VECTOR2_H
