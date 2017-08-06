#ifndef PANCAKE_TEXT
#define PANCAKE_TEXT

#include "Font.h"
#include "Renderable.h"

class Text {
public:
  const char* text;
  const Font* font;

  Text();
  
  void setFont(const Font* font);
  
  void setText(const char* text);
};

#endif
