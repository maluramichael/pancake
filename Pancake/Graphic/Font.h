#ifndef PANCAKE_FONT
#define PANCAKE_FONT

#include <ostream>
#include "Texture.h"
#include "stb_truetype.h"

template<typename T>
std::istream& binary_read(std::istream& stream, T& value) {
  return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value) {
  return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

class Font {
private:
  Texture texture;
  
  
  stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs

public:
  bool load(int textureSize);
  
  Texture& getTexture();
  
  void release() {
    texture.release();
  }
};

#endif
