//

//

#ifndef PANCAKE_BUTTON
#define PANCAKE_BUTTON

#include "Interface.h"
#include "Widget.h"

namespace Pancake {
  namespace UI {
    class Button : public Widget {
    public:
      Button() {
      }
      
      Button(int xpos, int y, int w, int h, const char* text, MouseClickCallback clicked) {
        this->x = xpos;
        this->y = y;
        this->w = w;
        this->h = h;
      }
      
      void render(const Pancake::Graphics::Painter& painter) {
        painter.fillRectangle({x, y}, {w, h}, {255, 255, 255, 255});
      }
      
      void render(float delta) {}
    };
  }
}

#endif //PANCAKE_BUTTON
