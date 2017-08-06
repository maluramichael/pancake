#ifndef PANCAKE_FONT
#define PANCAKE_FONT

#include <map>
#include "Texture.h"
#include "stb_truetype.h"

struct Glyph {
  float x0, y0, s0, t0; // top-left
  float x1, y1, s1, t1; // bottom-right
};

class Font {
private:

  std::map<char, stbtt_aligned_quad> glyphs;
  
public:
  Texture texture;

  bool load(int textureSize);
  
  Texture& getTexture();
  
  void release() {
    texture.release();
    //delete[] cdata;
  }
  
};

#endif
