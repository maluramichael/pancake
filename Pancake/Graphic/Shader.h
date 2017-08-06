#ifndef PANCAKE_SHADER
#define PANCAKE_SHADER

#include <GL/glew.h>
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <glm/vec2.hpp>
#include <Pancake/Game/File.h>

#include "../Math/Matrix.h"
#include "../Math/Vector2.h"

class Shader {
protected:
  
  typedef std::vector<GLuint> ShaderList;
  
  GLuint loadShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    
    const char* c = source.c_str();
    
    glShaderSource(shader, 1, &c, nullptr);
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status != GL_TRUE) {
      char buffer[512];
      glGetShaderInfoLog(shader, 512, nullptr, buffer);
      std::cout << (type == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShader") << " " << buffer << '\n';
      return 0;
    }
    
    return shader;
  }
  
  GLuint createProgram(ShaderList shaders) {
    GLuint program = glCreateProgram();
    for (auto shader : shaders) {
      glAttachShader(program, shader);
    }
    glLinkProgram(program);
    return program;
  }
  
  GLint getUniformLocation(std::string name) {
    return glGetUniformLocation(shaderProgram, name.c_str());
  }
  
  virtual void initialize() {};
  
  GLuint vertexShader = 0;
  
  GLuint fragmentShader = 0;
  
  GLuint shaderProgram = 0;
  
  
  std::map<std::string, GLuint> uniforms;
  
  File vertexShaderFile;
  
  File fragmentShaderFile;

public:
  GLuint vertexArray = 0;

  Shader() = default;;
  
  Shader(File vertexShaderFile, File fragmentShaderFile) : vertexShaderFile(std::move(vertexShaderFile)), fragmentShaderFile(std::move(fragmentShaderFile)) {
  }
  
  void release() {
    if (vertexShader != 0) {
      glDeleteShader(vertexShader);
      vertexShader = 0;
    }
    if (fragmentShader != 0) {
      glDeleteShader(fragmentShader);
      fragmentShader = 0;
    }
    if (shaderProgram != 0) {
      glDeleteProgram(shaderProgram);
      shaderProgram = 0;
    }
    if (vertexArray != 0) {
      glDeleteVertexArrays(1, &vertexArray);
      vertexArray = 0;
    }
  }
  
  bool load() {
    std::string vertexShaderSource = vertexShaderFile.readAll();
    std::string fragmentShaderSource = fragmentShaderFile.readAll();
    
    vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    shaderProgram = createProgram(ShaderList{vertexShader, fragmentShader});
    
    return true;
  }
  
  bool reload() {
    release();
    return load();
  }
  
  void begin() const {
    glUseProgram(shaderProgram);
    //glBindVertexArray(vertexArray);
  }
  
  void end() const {
    //glBindVertexArray(0);
    glUseProgram(0);
  }
  
  void loadUniforms(std::vector<std::string> names) {
    for (auto name: names) {
      GLuint location = (GLuint) getUniformLocation(name);
      if (location != 0) {
        uniforms[name] = location;
      } else {
        std::cout << "Location " << name << " could not be found\n";
      }
    }
  }
  
  void set(std::string name, float x) {
    glUniform1f(uniforms[name], x);
  }
  
  void set(std::string name, float x, float y) {
    glUniform2f(uniforms[name], x, y);
  }
  
  void set(std::string name, const glm::vec2& vec) {
    glUniform2f(uniforms[name], vec.x, vec.y);
  }
  
  void set(std::string name, float x, float y, float z) {
    glUniform3f(uniforms[name], x, y, z);
  }
  
  void set(std::string name, float x, float y, float z, float w) {
    glUniform4f(uniforms[name], x, y, z, w);
  }
  
  void set(std::string name, const Matrix& mat) {
    glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, mat.data);
  }
  
  void set(std::string name, const float* const mat) {
    glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, mat);
  }
  
  GLuint getProgram() const {
    return shaderProgram;
  }
  
  std::string vertexShaderSource;
  
  std::string fragmentShaderSource;
};

#endif //PANCAKE_SHADER
