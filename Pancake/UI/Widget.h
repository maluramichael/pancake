#ifndef PANCAKE_WIDGET
#define PANCAKE_WIDGET

#include "Interface.h"

class Widget : public Renderable {
protected:
  int x = 0;
  
  int y = 0;
  
  int w = 1;
  
  int h = 1;

public:
  virtual void render(float delta) {}
};

#endif
