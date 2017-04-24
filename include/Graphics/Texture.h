
#ifndef __PANCAKE__GRAPHICS__TEXTURE__
#define __PANCAKE__GRAPHICS__TEXTURE__

#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "../Math/Vector2.h"

namespace Pancake {
    namespace Graphics {
        class Texture {
        private:
            SDL_Texture* texture = nullptr;
            std::string filename = "";

            Math::Vector2 dimensions = Math::Vector2::Zero();
            Math::Vector2 scale = Math::Vector2::One();
            float rotation = 0;

        public:
            Texture(SDL_Texture* texture);

            ~Texture();

            void setFilename(const std::string& filename);

            const std::string& getFilename() const;

            SDL_Texture* getTexture() const;

            const Math::Vector2& getDimensions() const;

            void setDimensions(const Math::Vector2& dimensions);

            const Math::Vector2& getScale() const;

            void setScale(const Math::Vector2& scale);

            float getRotation() const;

            void setRotation(float rotation);


        };
    }
}

#endif