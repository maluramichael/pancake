#ifndef PANCAKE_OPENGL
#define PANCAKE_OPENGL

#include <GL/glew.h>

/**
 *
 */
struct VertexPosition {
  float x, y;
};
/**
 *
 */
struct VertexPositionTexture {
  float x, y, z, u, v;
};
/**
 *
 */
struct VertexPositionColor {
  float x, y, r, g, b;
};

/**
 *
 * @return
 */
GLuint createVertexArray();

/**
 *
 * @return
 */
GLuint createBuffer();

/**
 *
 * @return
 */
GLuint createVertexAttributePointer(GLuint shader, const char* name, short elements, GLenum type, short stride, short offsetInBytes, GLboolean normalize = GL_FALSE);

#endif
