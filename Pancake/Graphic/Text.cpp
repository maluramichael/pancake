#include "Text.h"

Text::Text() {
}

void Text::setFont(const Font* font) {
  this->font = font;
}

void Text::setText(const char* text) {
  this->text = text;
}