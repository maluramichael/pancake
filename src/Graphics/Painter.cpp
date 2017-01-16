//
// Created by Michael Malura on 22/11/16.
//

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../include/Graphics/Painter.h"
#include "../../include/Log.h"

namespace Pancake {

Painter::Painter(SDL_Renderer *r) : renderer(r) {}

SDL_Texture *Painter::loadTexture(const std::string &file) {
  std::cout << "Load texture: " << file << std::endl;
  SDL_Texture *texture = IMG_LoadTexture(this->renderer, file.c_str());
  if (texture == nullptr) {
    Pancake::logSDLError(std::cout, "LoadTexture");
  }
  return texture;
}

void Painter::drawTexture(Texture *texture, float x, float y, float w, float h,
                          float sx, float sy, float sw, float sh) {}

void Painter::drawTexture(const Texture &texture, float x, float y, float w,
                          float h) {
  SDL_Rect destination;
  destination.x = x;
  destination.y = y;
  destination.w = w;
  destination.h = h;
  SDL_RenderCopy(this->renderer, texture.getTexture(), nullptr, &destination);
}

void Painter::drawTexture(const Texture &texture, float x, float y) {
  drawTexture(texture, x, y, texture.getWidth(), texture.getHeight());
}

void Painter::drawTexture(const Texture &texture) {
  drawTexture(texture, 0, 0);
}

void Painter::drawLine(float x0, float y0, float x1, float y1) {
  aalineRGBA(this->renderer, x0, y0, x1, y1, 255, 0, 0, 255);
  // SDL_RenderDrawLine(this->renderer,x0, y0, x1, y1);
}

void Painter::setColor(short r = 255, short g = 255, short b = 255,
                       short a = 255) {
  SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void Painter::saveState() { currentState = PainterState(); }

void Painter::restoreState() {

  SDL_SetRenderDrawColor(this->renderer, this->currentState.getColor().red(),
                         this->currentState.getColor().green(),
                         this->currentState.getColor().blue(),
                         this->currentState.getColor().alpha());
}
}