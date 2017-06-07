#include "OpenGL.h"

GLuint createVertexArray() {
  GLuint id;
  glGenVertexArrays(1, &id);
  return id;
}

GLuint createBuffer() {
  GLuint id;
  glGenBuffers(1, &id);
  return id;
}

GLuint createVertexAttributePointer(GLuint shader, const char* name, short elements, GLenum type,
                                                       short stride, short offsetInBytes, GLboolean normalize) {
  auto id = glGetAttribLocation(shader, name);
  glVertexAttribPointer((GLuint) id, elements, type, normalize, stride, (void*) offsetInBytes);
  return (GLuint) id;
};
