#include <fstream>
#include "Font.h"
#include "../Game/ProfilerSample.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

bool Font::load(int textureSize = 512) {
  std::string filename = "res/ProggyClean.ttf";
  unsigned char* buffer;
  long size;
  std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
  size = file.tellg();
  file.seekg(0, std::ios::beg);
  buffer = new unsigned char[size];
  file.read(reinterpret_cast<char*>(buffer), size);
  file.close();
  
  stbtt_bakedchar* cdata = new stbtt_bakedchar[96]; // ASCII 32..126 is 95 glyphs
  
  unsigned char temp_bitmap[textureSize * textureSize];
  auto result = stbtt_BakeFontBitmap(buffer, 0, 32.0, temp_bitmap, textureSize, textureSize, 32, 96, cdata); // no guarantee this fits!
  
  float x, y;
  for(int i = 32; i<126; i++){
    stbtt_aligned_quad q;
    stbtt_GetBakedQuad(cdata, textureSize, textureSize, (char)i, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
    glyphs[(char)i] = q;
  }
  
  delete[] cdata;
  delete[] buffer;
  texture.generate();
  texture.begin();
  texture.setData(GL_TEXTURE_2D, 0, GL_ALPHA, textureSize, textureSize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  texture.end();
  return true;
}

Texture& Font::getTexture() {
  return texture;
}

