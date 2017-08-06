#ifndef PANCAKE_TEXTURE
#define PANCAKE_TEXTURE

#include <string>
#include <iostream>

#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#include "../Math/Vector2.h"

class Texture {
private:
  GLuint id = 0;

public:
  std::string filename = "";

  Vector2 dimensions;

  static Texture loadTexture(const std::string& file);
  
  Texture();
  
  Texture(GLuint id);
  
  void create();
  
  void setData(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
  
  void release();
  
  const Vector2& getDimensions() const;
  
  void setDimensions(Vector2 dimensions);
  
  void setFilename(const std::string& filename);
  
  const std::string& getFilename() const;
  
  void begin() const;
  
  void end() const;
  
  void generate();
};

#endif