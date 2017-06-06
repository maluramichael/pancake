#ifndef PANCAKE_FONT
#define PANCAKE_FONT

#include <ostream>
#include "../Graphic/Texture.h"
#include "../UI/stb_truetype.h"

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
  return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value){
  return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

namespace Pancake {
  
  class Font {
  private:
    Graphics::Texture texture;
  
    unsigned char temp_bitmap[512*512];
    stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
  
  public:
    bool load();
    
    void release() {
      texture.release();
    }
  };
}

#endif
