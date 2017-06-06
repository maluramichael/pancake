//

//

#include "Text.h"

Pancake::Graphics::Text::Text() {
}

void Pancake::Graphics::Text::setFont(const Pancake::Font* font) {
  this->font = font;
}

void Pancake::Graphics::Text::setText(const char* text) {
  this->text = text;
}
