#ifndef PANCAKE_MESH
#define PANCAKE_MESH

#include "Shader.h"
#include "Texture.h"
#include "OpenGL.h"

class Mesh {
private:
  //unsigned int vertexCount = 0, indexCount = 0;
  
  //Shader shader;
  
  //GLuint elementBuffer, vertexArray;
  
  //Texture texture;
  
  bool hasTexture = false;
  
  bool hasElementBuffer = false;
  
  bool hasArrayBuffer = false;
  
  bool hasShader = false;
  
  void activate() {
    activateBuffer();
    activateTexture();
    activateShader();
  }
  
  void activateBuffer() {
    if (hasElementBuffer) {}
    if (hasArrayBuffer) {}
  }
  
  void activateTexture() {
    if (hasTexture) {}
  }
  
  void activateShader() {
    if (hasShader) {}
  }
  
  void deactivate() {
    deactivateBuffer();
    deactivateTexture();
    deactivateShader();
  }
  
  void deactivateBuffer() {
    if (hasElementBuffer) {}
    if (hasArrayBuffer) {}
  }
  
  void deactivateTexture() {
    if (hasTexture) {}
  }
  
  void deactivateShader() {
    if (hasShader) {}
  }

public:
  void render() {
    activate();
    
    deactivate();
  }
  
  void setVertices(float* vertices, unsigned int vertexSizeInBytes) {
    hasArrayBuffer = true;
  }
  
  void setIndices(short* indices, unsigned int indexCount) {
    hasElementBuffer = true;
  }
  
  void setTexture(Texture texture) {
    hasTexture = true;
  }
  
  void setShader(Shader shader) {
    hasShader = true;
  }
};

#endif
