#ifndef PANCAKE_BUTTON
#define PANCAKE_BUTTON

#include "Widget.h"

class Button : public Widget {
public:
  Button() {
  }
  
  Button(int xpos, int y, int w, int h, const char* text, MouseClickCallback clicked) {
    this->position = {xpos, y, 0};
    this->size = {w, h, 1};
  }
  
  void render(Painter& painter) {
    if (hovered){
      painter.fillRectangle({this->position.x, this->position.y}, {this->size.x, this->size.y}, {255, 255, 255, 255});
    } else {
      painter.fillRectangle({this->position.x, this->position.y}, {this->size.x, this->size.y}, {100, 100, 100, 255});
    }
  }
  
  void render(float delta) {}
};

#endif
