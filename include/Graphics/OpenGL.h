//
// Created by Michael Malura on 27/04/17.
//

#ifndef PANCAKE_OPENGL_H
#define PANCAKE_OPENGL_H

#include <GL/glew.h>

namespace Pancake {
    namespace Graphics {

        struct VertexPosition {
            float x, y;
        };

        struct VertexPositionTexture {
            float x, y, z, u, v;
        };

        struct VertexPositionColor {
            float x, y, r, g, b;
        };

        GLuint createVertexArray();

        GLuint createBuffer();

        GLuint createVertexAttributePointer(GLuint shader, const char* name, short elements, GLenum type, short stride,
                                            short offsetInBytes, GLboolean normalize = GL_FALSE);
    }
}

#endif //PANCAKE_OPENGL_H
