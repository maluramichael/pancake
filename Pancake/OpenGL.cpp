//
// Created by Michael Malura on 27/04/17.
//

#include "OpenGL.h"

GLuint Pancake::Graphics::createVertexArray() {
    GLuint id;
    glGenVertexArrays(1, &id);
    return id;
}

GLuint Pancake::Graphics::createBuffer() {
    GLuint id;
    glGenBuffers(1, &id);
    return id;
}

GLuint Pancake::Graphics::createVertexAttributePointer(GLuint shader, const char* name, short elements, GLenum type,
                                                       short stride, short offsetInBytes, GLboolean normalize) {
    auto id = glGetAttribLocation(shader, name);
    glVertexAttribPointer((GLuint) id, elements, type, normalize, stride, (void*) offsetInBytes);
    return (GLuint) id;
};
