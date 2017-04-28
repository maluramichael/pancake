//
// Created by Michael Malura on 22/11/16.
//

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../include/Graphics/Painter.h"
#include "../../include/Log.h"
#include <GL/glew.h>

namespace Pancake {
    namespace Graphics {

        Painter::Painter(SDL_Renderer* r) : renderer(r) {
            initialize();
        }

        void Painter::initialize() {
            texture.generate();

            // Quad
            std::vector<VertexPositionTexture> quadVertices = {
                    {-0.5f, 0.5f,  0, 0}, // top left
                    {0.5f,  0.5f,  1, 0}, // top right
                    {0.5f,  -0.5f, 1, 1}, // bottom right
                    {-0.5f, -0.5f, 0, 1} // bottom left
            };

            GLuint vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(VertexPositionColor) * quadVertices.size(),
                         &quadVertices[0],
                         GL_STATIC_DRAW);


            // Shader
            const char* vsCode = "#version 150\n"
                    "\n"
                    "uniform mat4 mat;\n"
                    "in vec2 position;\n"
                    "in vec2 textureCoordinate;\n"
                    "out vec2 _textureCoordinate;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    _textureCoordinate = textureCoordinate;\n"
                    "    //vec2 pos = position * world;\n"
                    "    gl_Position = mat * vec4(position, 0.0, 1.0);\n"
                    "}";

            std::string fsCode = "#version 150\n"
                    "\n"
                    "in vec2 _textureCoordinate;\n"
                    "out vec4 outColor;\n"
                    "uniform sampler2D tex;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    outColor = texture(tex, _textureCoordinate) * vec4(1.0, 1.0, 1.0, 1.0);\n"
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
                                                                             2,
                                                                             GL_FLOAT,
                                                                             4 * sizeof(float),
                                                                             0);

            auto texAttirb = Pancake::Graphics::createVertexAttributePointer(shaderProgram,
                                                                             "textureCoordinate",
                                                                             2,
                                                                             GL_FLOAT,
                                                                             4 * sizeof(float),
                                                                             2 * sizeof(float));
            glEnableVertexAttribArray(posAttrib);
            glEnableVertexAttribArray(texAttirb);

            GLuint elements[] = { // clock wise 2 triangles
                    0, 1, 2, // top left, top right, bottom right
                    0, 2, 3 // top left, bottom right, bottom left
            };

            elementBuffer = createBuffer();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

            shader.end();

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glUseProgram(0);
        }

        Texture* Painter::loadTexture(const std::string& file) {
            std::cout << "Load texture: " << file << std::endl;
            auto sdlTexture = IMG_LoadTexture(this->renderer, file.c_str());
            if (sdlTexture == nullptr) {
                Pancake::logSDLError(std::cout, "LoadTexture");
            }

            auto texture = new Texture(sdlTexture);
            texture->setFilename(file);

            return texture;
        }

        void Painter::drawTexture(const Texture& texture, float x, float y, float w, float h, float ox, float oy,
                                  float rotation) {
            SDL_Rect destination;
            destination.x = x;
            destination.y = y;
            destination.w = w;
            destination.h = h;

            SDL_Point offset;
            offset.x = ox;
            offset.y = oy;

            SDL_RenderCopyEx(this->renderer, texture.getTexture(), nullptr, &destination, rotation, &offset,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y, float w, float h, float rotation) {
            drawTexture(texture, x, y, w, h, 0, 0, rotation);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y, float w, float h) {
            drawTexture(texture, x, y, w, h, 0);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y, float roation) {
            drawTexture(texture, x, y, texture.getDimensions().x, texture.getDimensions().y, roation);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y) {
            drawTexture(texture, x, y, 0);
        }

        void Painter::drawLine(float x0, float y0, float x1, float y1) {
            auto color = this->currentState.getColor();
            aalineRGBA(this->renderer, x0, y0, x1, y1, color.red(), color.green(), color.blue(), color.alpha());
            // SDL_RenderDrawLine(this->renderer,x0, y0, x1, y1);
        }

        void Painter::saveState() { currentState = PainterState(); }

        void Painter::restoreState() {
            auto color = this->currentState.getColor();
            SDL_SetRenderDrawColor(this->renderer, color.red(), color.green(), color.blue(), color.alpha());
        }

        void Painter::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            currentState.setColor((r << 24) | (g << 16) | (b << 8) | (a));
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
        }

        void Painter::drawRectangle(float x, float y, float w, float h) {
            boxColor(renderer, x, y, x + w, y + h, currentState.getColor().getColor());
        }

        void Painter::drawPixel(float x, float y) {
            pixelColor(renderer, x, y, currentState.getColor().getColor());
        }

        void Painter::drawRectangle(float x, float y, float w, float h, int color) {
            boxColor(renderer, x, y, x + w, y + h, color);
        }

        void Painter::drawPixel(float x, float y, int color) {
            pixelColor(renderer, x, y, color);
        }

        void Painter::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position) {
            drawTexture(texture, position, Math::Vector2(1, 1));
        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size) {
            drawTexture(texture, position, size, 0);
        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size,
                                  float rotation) {
            drawTexture(texture, position, size, rotation, Math::Vector2(0, 0));

        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size,
                                  float rotation, const Math::Vector2& origin) {
            float w = texture.getDimensions().x * size.x;
            float h = texture.getDimensions().y * size.y;

            SDL_Point offset;
            offset.x = origin.x * w;
            offset.y = origin.y * h;

            SDL_Rect destination;
            destination.x = position.x - offset.x;
            destination.y = position.y - offset.y;
            destination.w = w;
            destination.h = h;


            SDL_RenderCopyEx(this->renderer, texture.getTexture(), nullptr, &destination, rotation, &offset,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

        void Painter::drawTexture(const Texture& texture) {

        }

        void Painter::drawLine(const Math::Vector2& from, const Math::Vector2& to) {
            drawLine(from.x, from.y, to.x, to.y);
        }

        void Painter::drawPixel(const Math::Vector2& position) {
            drawPixel(position.x, position.y);
        }

        void Painter::drawRectangle(const Math::Vector2& position, const Math::Vector2& size) {
            drawRectangle(position.x, position.y, size.x, size.y);
        }

        void Painter::drawRawTexture(SDL_Texture* texture) {
            SDL_Rect destination;
            destination.x = 0;
            destination.y = 0;

            Uint32 format;
            int access;
            int w;
            int h;
            SDL_QueryTexture(texture, &format, &access, &w, &h);
            destination.w = w;
            destination.h = h;


            SDL_RenderCopy(this->renderer, texture, nullptr, &destination);
        }

        SDL_Renderer* Painter::getRenderer() const {
            return renderer;
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

    }
}