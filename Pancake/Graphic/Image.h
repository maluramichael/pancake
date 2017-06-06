#ifndef PANCAKE_IMAGE
#define PANCAKE_IMAGE

#include "Texture.h"
#include "Renderable.h"

namespace Pancake {
  namespace Graphics {
    class Image : public Renderable {
    private:
      Texture texture;
    };
  }
}

#endif
