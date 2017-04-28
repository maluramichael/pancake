//
// Created by Michael Malura on 22/11/16.
//

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../include/Graphics/Painter.h"
#include "../../include/Log.h"
#include <GL/glew.h>
#include <ilut.h>


namespace Pancake {
    namespace Graphics {

        Painter::Painter() {
            initialize();
        }

        void Painter::initialize() {
            // Initialize DEVIL image library
            ilInit();
            iluInit();
            ilutInit();
            ilutRenderer(ILUT_OPENGL);
            ilutEnable(ILUT_OPENGL_CONV);

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
            const char *vsCode = "#version 150\n"
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
                    "    outColor = texture(tex, _textureCoordinate) * vec4(1.0, 1.0, 0.0, 1.0);\n"
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

        Texture *Painter::loadTexture(const std::string &file) {
            std::cout << "Load texture: " << file << std::endl;

            ILuint ilID;
            ilGenImages(1, &ilID);
            ilBindImage(ilID);
            ilLoadImage(file.c_str());

            auto width = ilGetInteger(IL_IMAGE_WIDTH);
            auto height = ilGetInteger(IL_IMAGE_HEIGHT);
            auto palette = ilGetInteger(IL_PALETTE_TYPE);
            auto format = ilGetInteger(IL_IMAGE_FORMAT);
            auto bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
            bool convertedPalette = ilGetBoolean(IL_CONV_PAL);

            std::string paletteName = "";
            std::string formatName = "";

            switch (palette) {
                case IL_PAL_NONE: paletteName = "IL_PAL_NONE"; break;
                case IL_PAL_RGB24: paletteName = "IL_PAL_RGB24"; break;
                case IL_PAL_RGB32: paletteName = "IL_PAL_RGB32"; break;
                case IL_PAL_RGBA32: paletteName = "IL_PAL_RGBA32"; break;
                case IL_PAL_BGR24: paletteName = "IL_PAL_BGR24"; break;
                case IL_PAL_BGR32: paletteName = "IL_PAL_BGR32"; break;
                case IL_PAL_BGRA32: paletteName = "IL_PAL_BGRA32"; break;
            }

            switch (format) {
                case IL_COLOR_INDEX: formatName = "IL_COLOR_INDEX"; break;
                case IL_ALPHA: formatName = "IL_ALPHA"; break;
                case IL_RGB: formatName = "IL_RGB"; break;
                case IL_RGBA: formatName = "IL_RGBA"; break;
                case IL_BGR: formatName = "IL_BGR"; break;
                case IL_BGRA: formatName = "IL_BGRA"; break;
                case IL_LUMINANCE: formatName = "IL_LUMINANCE"; break;
                case IL_LUMINANCE_ALPHA: formatName = "IL_LUMINANCE_ALPHA"; break;
            }

            std::cout << "Converted: " << convertedPalette << " BPP: " << bpp << " Format: " << formatName << " Palette: " << paletteName << " (" << width << ", " << height << ")" << std::endl;

            uint8_t *pixmap = new uint8_t[width * height * bpp];
            ilCopyPixels(0, 0, 0, width, height, 1, format, IL_UNSIGNED_BYTE, pixmap);

            for (int i = 0; i < width * height * bpp; i += bpp) {
                std::cout << (int)pixmap[i] << ' ' << (int)pixmap[i + 1] << ' ' << (int)pixmap[i + 2] << ' ' << (int)pixmap[i + 3] << '\n';
            }

            ilBindImage(0);
            ilDeleteImage(ilID);

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

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixmap);

            glBindTexture(GL_TEXTURE_2D, 0);

            delete[] pixmap;

            auto texture = new Texture(glID);
            texture->setFilename(file);
//
//            ilDeleteImages(1, &ilID);

            return texture;
        }

        void Painter::drawQuad(const Pancake::Math::Matrix &mat) {
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

        void Painter::drawTexture(const Math::Matrix &mat, Texture *texture) {
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
            ilShutDown();
        }

        Painter::~Painter() {
            shutdown();
        }

    }
}