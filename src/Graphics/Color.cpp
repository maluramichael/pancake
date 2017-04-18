
#include "../../include/Graphics/Color.h"


namespace Pancake {
    namespace Graphics {

        Color::Color() {}

        Color::Color(short r, short g, short b, short a) : r(r), g(g), b(b), a(a) {

        }

        Color::Color(int color) {
            r = (short) ((color >> 24) & 0xFF);
            g = (short) ((color >> 16) & 0xFF);
            b = (short) ((color >> 8) & 0xFF);
            a = (short) (color & 0xFF);
        }

        void Color::lighten(float d) {}

        void Color::darken(float d) {}

        short Color::getHue() { return 0; }

        short Color::getSaturation() { return 0; }

        short Color::getValue() { return 0; }

        short Color::getLightness() { return 0; }

        short Color::getBrightness() { return 0; }

        short Color::getIntensity() { return 0; }

        short Color::red() { return r; }

        short Color::green() { return g; }

        short Color::blue() { return b; }

        short Color::alpha() { return a; }

        void Color::red(short v) { r = v; }

        void Color::green(short v) { g = v; }

        void Color::blue(short v) { b = v; }

        void Color::alpha(short v) { a = v; }

        int Color::getColor() {
            return (r << 24) | (g << 16) | (b << 8) | (a);
        }
    }
}