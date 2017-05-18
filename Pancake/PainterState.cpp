#include "PainterState.h"

namespace Pancake {
    namespace Graphics {
        PainterState::PainterState() {}

        Color PainterState::getColor() { return color; }

        void PainterState::setColor(short r, short g, short b, short a) {
            this->color = Color(r, g, b, a);
        }

        void PainterState::setColor(int color) {
            this->color = Color(color);

        }

        void PainterState::setColor(Color color) {
            this->color = color;
        }
    }
}