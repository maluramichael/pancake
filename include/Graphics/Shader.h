//
// Created by Michael Malura on 27/04/17.
//

#ifndef PANCAKE_SHADER_H
#define PANCAKE_SHADER_H

#include <GL/glew.h>
#include <vector>
#include <iostream>

namespace Pancake {
    namespace Graphics {
        class Shader {
        private:

            typedef std::vector<GLuint> ShaderList;

            GLuint loadShader(GLenum type, std::string source) {
                GLuint shader = glCreateShader(type);
                const char* c = source.c_str();

                glShaderSource(shader, 1, &c, NULL);
                glCompileShader(shader);

                GLint status;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

                if (status != GL_TRUE) {
                    char buffer[512];
                    glGetShaderInfoLog(shader, 512, NULL, buffer);
                    std::cout << buffer << '\n';
                    return 0;
                }

                return shader;
            }

            GLuint loadFragmentShader(std::string source) { return loadShader(GL_FRAGMENT_SHADER, source); }

            GLuint loadVertexShader(std::string source) { return loadShader(GL_VERTEX_SHADER, source); }

            GLuint createProgram(ShaderList shaders) {
                GLuint program = glCreateProgram();
                for (auto shader : shaders) {
                    glAttachShader(program, shader);
                }
                glLinkProgram(program);
                return program;
            }

            GLuint vertexShader = 0;
            GLuint fragmentShader = 0;
            GLuint shaderProgram = 0;

            std::string vertexShaderSource;
            std::string fragmentShaderSource;

        public:
            Shader() {}

            Shader(std::string vertexShader, std::string fragmentShader) : vertexShaderSource(vertexShader),
                                                                           fragmentShaderSource(fragmentShader) {
            }

            void setVertexShaderSource(std::string vertexShaderSource) {
                this->vertexShaderSource = vertexShaderSource;
            }

            void setFragmentShaderSource(std::string fragmentShaderSource) {
                this->fragmentShaderSource = fragmentShaderSource;
            }

            bool load() {
                vertexShader = loadVertexShader(vertexShaderSource);
                fragmentShader = loadFragmentShader(fragmentShaderSource);
                shaderProgram = createProgram(ShaderList{vertexShader, fragmentShader});

                return true;
            }

            void begin() {
                glUseProgram(shaderProgram);
            }

            void end() {
                glUseProgram(0);
            }

            GLuint getProgram() const {
                return shaderProgram;
            }
        };
    }
}

#endif //PANCAKE_SHADER_H
