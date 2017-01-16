
#ifndef __PANCAKE__GRAPHICS__PAINTER__STATE__
#define __PANCAKE__GRAPHICS__PAINTER__STATE__

#include "Color.h"

namespace Pancake {

class PainterState {
private:
  Color color;

public:
  PainterState();
  Color getColor();
};
}

#endif