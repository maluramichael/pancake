//
// Created by Michael Malura on 22/11/16.
//

#include "../../include/Graphics/Texture.h"

namespace Pancake {
    namespace Graphics {

        Texture::Texture() {
        }

        void Texture::begin() {
            glBindTexture(GL_TEXTURE_2D, tex);
        }

        void Texture::end() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void Texture::generate() {
            if (tex != 0) return;
            glGenTextures(1, &tex);
            begin();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glGenerateMipmap(GL_TEXTURE_2D);

            // Black/white checkerboard
            float pixels[] = {
                    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
            };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
            end();
        }

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
            if (tex != 0) glDeleteTextures(1, &tex);
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