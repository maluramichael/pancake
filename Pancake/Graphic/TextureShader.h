#ifndef PANCAKE_TEXTURESHADER
#define PANCAKE_TEXTURESHADER

#include "Shader.h"
#include "OpenGL.h"

class TextureShader : public Shader {
public:
  
  void initialize() {
    auto vertexShaderSource = "#version 150\n"
      "\n"
      "uniform mat4 mat;\n"
      "in vec3 position;\n"
      "in vec2 textureCoordinate;\n"
      "out vec2 _textureCoordinate;\n"
      "void main()\n"
      "{\n"
      "    _textureCoordinate = textureCoordinate;\n"
      "    gl_Position = mat * vec4(position, 1.0);\n"
      "}";
    auto fragmentShaderSource = "#version 150\n"
      "\n"
      "in vec2 _textureCoordinate;\n"
      "out vec4 outColor;\n"
      "uniform sampler2D tex;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    outColor = texture(tex, _textureCoordinate);\n"
      "}";
    
    load();
    loadUniforms(std::vector<std::string>{"mat"});
    begin();
    
    auto vertexArray = createVertexArray();
    glBindVertexArray(vertexArray);
    
    auto positionAttribute = createVertexAttributePointer(shaderProgram,
                                                          "position",
                                                          3,
                                                          GL_FLOAT,
                                                          5 * sizeof(float),
                                                          0);
    auto textureAttribute = createVertexAttributePointer(shaderProgram,
                                                         "textureCoordinate",
                                                         2,
                                                         GL_FLOAT,
                                                         5 * sizeof(float),
                                                         3 * sizeof(float));
    glEnableVertexAttribArray(positionAttribute);
    glEnableVertexAttribArray(textureAttribute);
    
    end();
    glBindVertexArray(0);
  }
  
  void destroy() {
    release();
  }
};

#endif
