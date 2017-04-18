
#ifndef __PANCAKE__GRAPHICS__TEXTURE__
#define __PANCAKE__GRAPHICS__TEXTURE__

#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

namespace Pancake {
    namespace Graphics {
        class Texture {
        private:
            int width = 0, height = 0;
            SDL_Texture* texture = nullptr;
            std::string filename = "";

        public:
            Texture(SDL_Texture* texture);

            ~Texture();

            void setFilename(const std::string& filename);

            const std::string& getFilename() const;

            SDL_Texture* getTexture() const;

            int getWidth() const;

            int getHeight() const;
        };
    }
}

#endif