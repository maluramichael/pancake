
#include "../../include/Graphics/Color.h"

namespace Pancake {

Color::Color() { r = g = b = a = 0; }
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
}