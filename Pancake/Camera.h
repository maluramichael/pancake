//
// Created by Michael Malura on 25/04/17.
//
#pragma once
#ifndef PANCAKE_CAMERA_H
#define PANCAKE_CAMERA_H

#include "Rect.h"
#include "Vector2.h"

namespace Pancake {
    namespace Game {

        class Camera : public Pancake::Math::Rect {
        public:
            Camera() : Rect(Math::Vector2(0, 0), Math::Vector2(100, 100)) {

            }
        };

    }
}
#endif //PANCAKE_CAMERA_H
