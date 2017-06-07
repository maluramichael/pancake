#ifndef PANCAKE_TEXT
#define PANCAKE_TEXT

#include "../Graphic/Font.h"
#include "../Graphic/Renderable.h"

class Text : public Renderable {
  const char* text;
  
  const Font* font;

public:
  Text();
  
  void setFont(const Font* font);
  
  void setText(const char* text);
};

#endif
