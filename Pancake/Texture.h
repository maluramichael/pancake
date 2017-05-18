#pragma once

#ifndef PANCAKE_GRAPHICS_TEXTURE_H
#define PANCAKE_GRAPHICS_TEXTURE_H

#include <string>
#include <iostream>

#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Vector2.h"

namespace Pancake {
    namespace Graphics {
        class Texture {
        private:
            std::string filename = "";
            GLuint id = 0;
            Pancake::Math::Vector2 dimensions;

        public:
            static Texture loadTexture(const std::string& file);

            Texture();

            Texture(GLuint id);

            void release();

            const Math::Vector2& getDimensions() const;

            void setDimensions(Math::Vector2 dimensions);

            void setFilename(const std::string &filename);

            const std::string &getFilename() const;

            void begin();

            void end();

            void generate();

        };
    }
}

#endif