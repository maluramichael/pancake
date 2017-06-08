#ifndef PANCAKE_IMAGE
#define PANCAKE_IMAGE

#include "Texture.h"
#include "Renderable.h"

class Image : public Renderable {
private:
  Texture texture;
};

#endif
