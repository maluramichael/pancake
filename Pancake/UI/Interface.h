//

//

#ifndef PANCAKE_INTERFACE
#define PANCAKE_INTERFACE

#include <vector>
#include <functional>

#include "Widget.h"

typedef std::function<void(void)> MouseClickCallback;

class Widget;

class Interface {

public:
  typedef Widget* WidgetHandle;
  
  typedef std::vector<WidgetHandle> WidgetHandleList;
  
  WidgetHandleList widgets;
  
  void render(Pancake::Graphics::Painter& painter) {
  }
  
  void update(float delta) {
  }
  
  void addWidget(WidgetHandle handle) {
    widgets.push_back(handle);
  }
  
  void destroy() {
    for (auto& widget: widgets) {
      delete widget;
      widget = 0;
    }
  }
};

#endif //PANCAKE_INTERFACE
