#ifndef PANCAKE_TEXT
#define PANCAKE_TEXT

#include "Font.h"
#include "Renderable.h"

class Text {
  const char* text;
  
  const Font* font;

public:
  Text();
  
  void setFont(const Font* font);
  
  void setText(const char* text);
  
  const char* getText() const;
  
  const Font* getFont() const;
};

#endif
