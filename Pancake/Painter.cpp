//
// Created by Michael Malura on 22/11/16.
//

#include "Painter.h"
#include "Log.h"

namespace Pancake {
    namespace Graphics {

        Painter::Painter() {
        }

        Painter::Painter(Pancake::Math::Rect& camera, Math::Rect& screen) : camera(&camera), screen(&screen) {
//            initialize();
        }

        void Painter::initalizeLine() {

            glGenBuffers(1, &lineVertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);

            // Line shader
            std::string vertexShader = "#version 150\n"
                    "\n"
                    "uniform mat4 mat;\n"
                    "in vec2 position;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = mat * vec4(position, 0.0, 1.0);\n"
                    "}";

            std::string fragmentShader = "#version 150\n"
                    "\n"
                    "out vec4 outColor;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
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
                                                                                     0,
                                                                                     0);
            glEnableVertexAttribArray(positionAttribute);
            lineShader.end();
        }

        void Painter::initalizeQuad() {

            GLuint vertexBuffer;
            glGenBuffers(1, &vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColor) * quadVertices.size(), &quadVertices[0],
                         GL_STATIC_DRAW);


            // Quad shader
            std::string vertexShader = "#version 150\n"
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

        /**
         * Currently this methods needs a full matrix (model, view and projection).
         * Later i want to the user to just pass a model matrix or some basic x,y,z coordinates and handle all the
         * projection and camera stuff inside the painter.
         */
        void Painter::drawTexture(const glm::mat4& mat, Pancake::Graphics::Texture& texture) {
            glBindVertexArray(quadVertexArray);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadElementBuffer);

            glm::mat4 projection = glm::ortho(0.0f, screen->w, screen->h, 0.0f, -5.0f, 5.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->x, -camera->y, 0));

            auto mvp = projection * view * mat;

            quadShader.begin();
            quadShader.set("mat", glm::value_ptr(mvp));

            texture.begin();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            texture.end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            quadShader.end();
        }

        void Painter::drawTexture(const glm::mat4& mat) {
            drawTexture(mat, texture);
        }

        void Painter::drawLine(Math::Vector2 from, Math::Vector2 to) {

            glm::mat4 projection = glm::ortho(0.0f, screen->w, screen->h, 0.0f, -5.0f, 5.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->x, -camera->y, 0));

            auto mvp = projection * view;

            lineVertices[0] = from.x;
            lineVertices[1] = from.y;
            lineVertices[2] = to.x;
            lineVertices[3] = to.y;

            glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVertices), lineVertices);
            glBindVertexArray(lineVertexArray);

            lineShader.begin();
            lineShader.set("mat", glm::value_ptr(mvp));

            glDrawArrays(GL_LINES, 0, 2);
            lineShader.end();
            glBindVertexArray(0);
        }

        void Painter::cleanup() {

        }

    }
}