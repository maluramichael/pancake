
#ifndef __PANCAKE__GRAPHICS__PAINTER__
#define __PANCAKE__GRAPHICS__PAINTER__

#include <SDL2/SDL_image.h>
#include <string>

#include "Texture.h"
#include "PainterState.h"

namespace Pancake {

class Painter {
public:
  Painter(SDL_Renderer *r);

  SDL_Texture *loadTexture(const std::string &file);

  void drawTexture(Texture *texture, float x, float y, float w, float h,
                   float sx, float sy, float sw, float sh);

  void drawTexture(const Texture &texture, float x, float y, float w, float h);

  void drawTexture(const Texture &texture, float x, float y);

  void drawTexture(const Texture &texture);

  void drawLine(float x0, float y0, float x1, float y1);

  void setColor(short r, short g, short b, short a);

  void saveState();

  void restoreState();

private:
  SDL_Renderer *renderer;
  PainterState currentState;
};
}

#endif