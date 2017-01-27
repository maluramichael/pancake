
#ifndef __PANCAKE__GRAPHICS__COLOR__
#define __PANCAKE__GRAPHICS__COLOR__
namespace Pancake {
    class Color {
    private:
        short r = 255, g = 255, b = 255, a = 255;

    public:
        Color();

        Color(short r, short g, short b, short a);

        Color(int color);

        void lighten(float d);

        void darken(float d);

        int getColor();

        short getHue();

        short getSaturation();

        short getValue();

        short getLightness();

        short getBrightness();

        short getIntensity();

        short red();

        short green();

        short blue();

        short alpha();

        void red(short v);

        void green(short v);

        void blue(short v);

        void alpha(short v);
    };
}
#endif