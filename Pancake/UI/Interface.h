#ifndef PANCAKE_INTERFACE
#define PANCAKE_INTERFACE

#include <vector>
#include <functional>

#include "Widget.h"
#include "../Graphic/Painter.h"

typedef std::function<void(void)> MouseClickCallback;

class Interface {

public:
  typedef Widget* WidgetHandle;
  
  typedef std::vector<WidgetHandle> WidgetHandleList;
  
  WidgetHandleList widgets;
  
  void render(Painter& painter) {
    for (auto& widget: widgets) {
      widget->render(painter);
    }
  }
  
  void update(float delta) {
  }
  
  void addWidget(WidgetHandle handle) {
    widgets.push_back(handle);
  }
  
  void initialize() {
  }
  
  void processEvent(SDL_Event* event) {
    for (auto& widget:widgets) {
      widget->processEvent(event);
    }
  }
  
  void destroy() {
    for (auto& widget: widgets) {
      delete widget;
      widget = 0;
    }
  }
};

#endif
