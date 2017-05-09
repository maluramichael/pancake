//
// Created by Michael Malura on 22/11/16.
//
#include <imgui.h>

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../include/Graphics/Painter.h"
#include "../../include/Log.h"
#include <GL/glew.h>

#include "../../libs/stb/stb.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../../libs/stb/stb_image.h"


namespace Pancake {
    namespace Graphics {

        Painter::Painter(Pancake::Game::Camera& camera, Math::Rect& screen) : camera(camera), screen(screen) {
            initialize();
        }

        void Painter::initalizeLine() {

            glGenBuffers(1, &lineVertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColor) * lineVertices.size(), &lineVertices[0], GL_DYNAMIC_DRAW);

            // Line shader
            const char* vertexShader = "#version 150\n"
                    "\n"
                    "uniform mat4 mat;\n"
                    "in vec2 position;\n"
                    "in vec3 color;\n"
                    "out vec3 c;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    c = color;\n"
                    "    gl_Position = mat * vec4(position, 0.0, 1.0);\n"
                    "}";

            std::string fragmentShader = "#version 150\n"
                    "\n"
                    "in vec3 c;\n"
                    "out vec4 outColor;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    outColor = vec4(c,255);\n"
                    "}";

            lineShader.setFragmentShaderSource(fragmentShader);
            lineShader.setVertexShaderSource(vertexShader);
            lineShader.load();
            lineShader.loadUniforms(std::vector<std::string>{"mat"});
            lineShader.begin();

            auto program = lineShader.getProgram();
            lineVertexArray = createVertexArray();
            glBindVertexArray(lineVertexArray);

            auto positionAttribute = Pancake::Graphics::createVertexAttributePointer(program,
                                                                                     "position",
                                                                                     2,
                                                                                     GL_FLOAT,
                                                                                     5 * sizeof(float),
                                                                                     0);

            auto colorAttribute = Pancake::Graphics::createVertexAttributePointer(program,
                                                                                    "color",
                                                                                    3,
                                                                                    GL_FLOAT,
                                                                                    5 * sizeof(float),
                                                                                    2 * sizeof(float));
            glEnableVertexAttribArray(positionAttribute);
            glEnableVertexAttribArray(colorAttribute);

//            GLuint elements[] = { // clock wise 2 triangles
//                    0, 1, 2, // top left, top right, bottom right
//                    0, 2, 3 // top left, bottom right, bottom left
//            };

//            lineElementBuffer = createBuffer();
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineElementBuffer);
//            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

            lineShader.end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glUseProgram(0);
        }

        void Painter::initalizeQuad() {

            GLuint vertexBuffer;
            glGenBuffers(1, &vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColor) * quadVertices.size(), &quadVertices[0],
                         GL_STATIC_DRAW);


            // Quad shader
            const char* vertexShader = "#version 150\n"
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

            std::string fragmentShader = "#version 150\n"
                    "\n"
                    "in vec2 _textureCoordinate;\n"
                    "out vec4 outColor;\n"
                    "uniform sampler2D tex;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    outColor = texture(tex, _textureCoordinate);\n"
                    "}";

            quadShader.setFragmentShaderSource(fragmentShader);
            quadShader.setVertexShaderSource(vertexShader);
            quadShader.load();
            quadShader.loadUniforms(std::vector<std::string>{"mat"});
            quadShader.begin();

            auto program = quadShader.getProgram();
            quadVertexArray = createVertexArray();
            glBindVertexArray(quadVertexArray);

            auto positionAttribute = Pancake::Graphics::createVertexAttributePointer(program,
                                                                                     "position",
                                                                                     3,
                                                                                     GL_FLOAT,
                                                                                     5 * sizeof(float),
                                                                                     0);

            auto textureAttribute = Pancake::Graphics::createVertexAttributePointer(program,
                                                                                    "textureCoordinate",
                                                                                    2,
                                                                                    GL_FLOAT,
                                                                                    5 * sizeof(float),
                                                                                    3 * sizeof(float));
            glEnableVertexAttribArray(positionAttribute);
            glEnableVertexAttribArray(textureAttribute);

            GLuint elements[] = { // clock wise 2 triangles
                    0, 1, 2, // top left, top right, bottom right
                    0, 2, 3 // top left, bottom right, bottom left
            };

            quadElementBuffer = createBuffer();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadElementBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

            quadShader.end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glUseProgram(0);
        }

        void Painter::initialize() {
            /* /////////////////////////////////////////////////////////
             * DEFAULT TEXTURE
             * ////////////////////////////////////////////////////// */
            texture.generate();

            /* /////////////////////////////////////////////////////////
             * QUAD
             * ////////////////////////////////////////////////////// */
            this->initalizeQuad();

            /* /////////////////////////////////////////////////////////
             * LINE
             * ////////////////////////////////////////////////////// */
            this->initalizeLine();
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
            texture->setDimensions({x, y});
            return texture;
        }

        void Painter::drawQuad(const Pancake::Math::Matrix& mat) {
            glBindVertexArray(quadVertexArray);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadElementBuffer);

            quadShader.begin();
            quadShader.set("mat", mat);

            texture.begin();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            texture.end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            quadShader.end();
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
            glBindVertexArray(quadVertexArray);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadElementBuffer);

            glm::mat4 projection = glm::ortho(0.0f, screen.w, screen.h, 0.0f, -5.0f, 5.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera.x, -camera.y, 0));

            auto mvp = projection * view * mat;

            quadShader.begin();
            quadShader.set("mat", glm::value_ptr(mvp));

            texture->begin();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            texture->end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            quadShader.end();
        }

        void Painter::drawTexture(const glm::mat4& mat) {
            drawTexture(mat, &texture);
        }

        void Painter::drawLine(Math::Vector2 from, Math::Vector2 to) {
            glBindVertexArray(lineVertexArray);

            // Update buffer data
            lineVertices[0].x = from.x;
            lineVertices[0].y = from.y;
            lineVertices[1].x = to.x;
            lineVertices[1].y = to.y;
            glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColor) * lineVertices.size(), &lineVertices[0], GL_DYNAMIC_DRAW);

//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineElementBuffer);

            glm::mat4 projection = glm::ortho(0.0f, screen.w, screen.h, 0.0f, -5.0f, 5.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera.x, -camera.y, 0));

            auto mvp = projection * view;

            lineShader.begin();
            lineShader.set("mat", glm::value_ptr(mvp));

            glDrawArrays(GL_LINE, 0, 2);

            glBindVertexArray(0);
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            lineShader.end();
        }

    }
}