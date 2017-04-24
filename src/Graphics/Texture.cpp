//
// Created by Michael Malura on 22/11/16.
//

#include "../../include/Graphics/Texture.h"

namespace Pancake {
    namespace Graphics {

        Texture::Texture(SDL_Texture* texture) : texture(texture) {
            if (texture != nullptr) {
                int width = 0, height = 0;
                SDL_QueryTexture(texture, NULL, NULL, &width, &height);
                setDimensions(Math::Vector2(width, height));
            }
        }

        Texture::~Texture() {
            if (texture != nullptr) {
                SDL_DestroyTexture(texture);
            }
        }

        SDL_Texture* Texture::getTexture() const { return texture; }

        void Texture::setFilename(const std::string& filename) { Texture::filename = filename; }

        const std::string& Texture::getFilename() const { return filename; }

        const Math::Vector2& Texture::getDimensions() const { return dimensions; }

        void Texture::setDimensions(const Math::Vector2& dimensions) { Texture::dimensions = dimensions; }

        const Math::Vector2& Texture::getScale() const { return scale; }

        void Texture::setScale(const Math::Vector2& scale) { Texture::scale = scale; }

        float Texture::getRotation() const { return rotation; }

        void Texture::setRotation(float rotation) { Texture::rotation = rotation; }
    }
}