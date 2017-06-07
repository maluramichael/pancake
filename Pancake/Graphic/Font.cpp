#include <fstream>
#include "Font.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "../UI/stb_truetype.h"

bool Font::load() {
  
  std::string filename = "res/ProggyClean.ttf";
  unsigned char* buffer;
  long size;
  std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
  size = file.tellg();
  file.seekg(0, std::ios::beg);
  buffer = new unsigned char[size];
  file.read(reinterpret_cast<char*>(buffer), size);
  file.close();
  
  std::cout << "the complete file is in a buffer " << size << "\n";
  
  stbtt_BakeFontBitmap(buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
  delete[] buffer;
  texture.create();
  texture.begin();
  texture.setData(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  texture.end();
  return true;
}
