#ifndef PANCAKE_WIDGET
#define PANCAKE_WIDGET

#include <SDL2/SDL_events.h>
#include "../Graphic/Renderable.h"

class Widget : public Renderable {
protected:
  bool hovered = false;

public:
  void processEvent(SDL_Event* event) {
    if (event->type == SDL_MOUSEMOTION) {
      int x = event->motion.x;
      int y = event->motion.y;
      
      if (x >= this->position.x && x <= this->position.x + this->size.x &&
          y >= this->position.y && y <= this->position.y + this->size.y) {
        hovered = true;
      } else if (hovered) {
        hovered = false;
      }
    }
  }
};

#endif
