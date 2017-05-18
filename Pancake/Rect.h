//
// Created by Michael Malura on 24/04/17.
//

#ifndef PANCAKE_RECT_H
#define PANCAKE_RECT_H

#include "Vector2.h"

namespace Pancake {
    namespace Math {
        class Rect {
        private:

        public:
            float x, y, w, h;

            Rect();

            Rect(Vector2 position, Vector2 size);

            Rect(float x, float y, float w, float h);

            void expand(float v);

            void shrink(float v);

            float getLeft();

            float getRight();

            float getTop();

            float getBottom();

            float getX();

            float getY();

            float getWidth();

            float getHeight();

            void setX(float x);

            void setY(float y);

            void setWidth(float w);

            void setHeight(float h);

            void setPosition(Vector2 position);

            void setSize(Vector2 size);

            Vector2 getPosition();

            Vector2 getSize();

            bool isInside(Vector2 point);

            bool isOutside(Vector2 point);
        };
    }
}
#endif //PANCAKE_RECT_H
