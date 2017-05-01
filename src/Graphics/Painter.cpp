//
// Created by Michael Malura on 22/11/16.
//

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../include/Graphics/Painter.h"
#include "../../include/Log.h"
#include <GL/glew.h>

#include "../../libs/stb/stb.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../../libs/stb/stb_image.h"


namespace Pancake {
    namespace Graphics {

        Painter::Painter() {
            initialize();
        }

        void Painter::initialize() {

            view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0));
            texture.generate();

            // Quad
            std::vector<VertexPositionTexture> quadVertices = {
                    {-0.5f, 0.5f,  0, 0, 0}, // top left
                    {0.5f,  0.5f,  0, 1, 0}, // top right
                    {0.5f,  -0.5f, 0, 1, 1}, // bottom right
                    {-0.5f, -0.5f, 0, 0, 1} // bottom left
            };

            GLuint vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(VertexPositionColor) * quadVertices.size(),
                         &quadVertices[0],
                         GL_STATIC_DRAW);


            // Quad shader
            const char* vsCode = "#version 150\n"
                    "\n"
                    "uniform mat4 mat;\n"
                    "in vec3 position;\n"
                    "in vec2 textureCoordinate;\n"
                    "out vec2 _textureCoordinate;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    _textureCoordinate = textureCoordinate;\n"
                    "    gl_Position = mat * vec4(position, 1.0);\n"
                    "}";

            std::string fsCode = "#version 150\n"
                    "\n"
                    "in vec2 _textureCoordinate;\n"
                    "out vec4 outColor;\n"
                    "uniform sampler2D tex;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    outColor = texture(tex, _textureCoordinate);\n"
                    "}";

            shader.setFragmentShaderSource(fsCode);
            shader.setVertexShaderSource(vsCode);
            shader.load();
            shader.loadUniforms(std::vector<std::string>{"world"});
            shader.begin();
            auto shaderProgram = shader.getProgram();

            vertexArray = createVertexArray();
            glBindVertexArray(vertexArray);
            auto posAttrib = Pancake::Graphics::createVertexAttributePointer(shaderProgram,
                                                                             "position",
                                                                             3,
                                                                             GL_FLOAT,
                                                                             5 * sizeof(float),
                                                                             0);

            auto texAttirb = Pancake::Graphics::createVertexAttributePointer(shaderProgram,
                                                                             "textureCoordinate",
                                                                             2,
                                                                             GL_FLOAT,
                                                                             5 * sizeof(float),
                                                                             3 * sizeof(float));
            glEnableVertexAttribArray(posAttrib);
            glEnableVertexAttribArray(texAttirb);

            GLuint elements[] = { // clock wise 2 triangles
                    0, 1, 2, // top left, top right, bottom right
                    0, 2, 3 // top left, bottom right, bottom left
            };

            elementBuffer = createBuffer();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

            shader.set("view", glm::value_ptr(view));
            shader.end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glUseProgram(0);
        }

        Texture* Painter::loadTexture(const std::string& file) {
            std::cout << "Load texture: " << file << std::endl;

            int x, y, n;
            unsigned char* data = stbi_load(file.c_str(), &x, &y, &n, 0);

            GLenum format;

            switch (n) {
                case 1:
                    format = GL_ALPHA;
                case 2:
                    format = GL_ALPHA;
                case 3:
                    format = GL_RGB;
                case 4:
                default:
                    format = GL_RGBA;
            }

            GLuint glID;
            glGenTextures(1, &glID);

            glBindTexture(GL_TEXTURE_2D, glID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0, format, GL_UNSIGNED_BYTE, data);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(data);

            auto texture = new Texture(glID);
            texture->setFilename(file);
            return texture;
        }

        void Painter::drawQuad(const Pancake::Math::Matrix& mat) {
            glBindVertexArray(vertexArray);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

            shader.begin();
            shader.set("mat", mat);

            texture.begin();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            texture.end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            shader.end();
        }

        void Painter::drawTexture(const Math::Matrix& mat, Texture* texture) {
            glBindVertexArray(vertexArray);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

            shader.begin();
            shader.set("mat", mat);
            texture->begin();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            texture->end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            shader.end();
        }

        void Painter::shutdown() {
        }

        Painter::~Painter() {
            shutdown();
        }

        /**
         * Currently this methods needs a full matrix (model, view and projection).
         * Later i want to the user to just pass a model matrix or some basic x,y,z coordinates and handle all the
         * projection and camera stuff inside the painter.
         */
        void Painter::drawTexture(const glm::mat4& mat, Pancake::Graphics::Texture* texture) {
            glBindVertexArray(vertexArray);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

            shader.begin();
            shader.set("mat", glm::value_ptr(mat));

            texture->begin();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            texture->end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            shader.end();
        }

    }
}