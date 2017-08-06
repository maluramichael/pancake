#ifndef PANCAKE_SUBTEXTURESHADER
#define PANCAKE_SUBTEXTURESHADER

#include "Shader.h"
#include "OpenGL.h"

class SubTextureShader : public Shader {
public:
  
  SubTextureShader(File vertexShaderFile, File fragmentShaderFile) : Shader(vertexShaderFile, fragmentShaderFile) {
  }
  
  void initialize() override {
    //auto vertexShaderSource = "#version 150\n"
    //  "\n"
    //  "uniform mat4 mat;\n"
    //  "in vec3 position;\n"
    //  "in vec2 textureCoordinate;\n"
    //  "out vec2 _textureCoordinate;\n"
    //  "void main()\n"
    //  "{\n"
    //  "    _textureCoordinate = textureCoordinate;\n"
    //  "    gl_Position = mat * vec4(position, 1.0);\n"
    //  "}";
    //
    //auto fragmentShaderSource = "#version 150\n"
    //  "\n"
    //  "uniform vec2 from;\n"
    //  "uniform vec2 to;\n"
    //  "uniform vec2 dimensions;\n"
    //  "in vec2 _textureCoordinate;\n"
    //  "out vec4 outColor;\n"
    //  "uniform sampler2D tex;\n"
    //  "\n"
    //  "void main()\n"
    //  "{\n"
    //  "    \n"
    //  "    outColor = texture(tex, (_textureCoordinate + from) * to);\n"
    //  "}";
    
    load();
    loadUniforms(std::vector<std::string>{"mat", "from", "to", "dimensions"});
    begin();
    
    vertexArray = createVertexArray();
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
