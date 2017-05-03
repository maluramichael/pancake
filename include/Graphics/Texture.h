
#ifndef __PANCAKE__GRAPHICS__TEXTURE__
#define __PANCAKE__GRAPHICS__TEXTURE__

#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <GL/glew.h>

#include "../Math/Vector2.h"

namespace Pancake {
    namespace Graphics {
        class Texture {
        private:
            std::string filename = "";
            GLuint id = 0;
            Pancake::Math::Vector2 dimensions;

        public:

            Texture();

            Texture(GLuint id);

            ~Texture();

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