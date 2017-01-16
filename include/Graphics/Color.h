
#ifndef __PANCAKE__GRAPHICS__COLOR__
#define __PANCAKE__GRAPHICS__COLOR__
namespace Pancake {
class Color {
private:
  short r, g, b, a;

public:
  Color();
  void lighten(float d);
  void darken(float d);
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