//
// Created by Michael Malura on 22/11/16.
//

#include "../../include/Graphics/Texture.h"

namespace Pancake {
    namespace Graphics {

        Texture::Texture() {
        }

        Texture::Texture(GLuint id) : id(id) {
        }

        void Texture::begin() {
            glBindTexture(GL_TEXTURE_2D, id);
        }

        void Texture::end() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void Texture::generate() {
            if (id != 0) return;
            glGenTextures(1, &id);
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

    
        Texture::~Texture() {
            if (id != 0) glDeleteTextures(1, &id);
        }

        void Texture::setFilename(const std::string& filename) { Texture::filename = filename; }

        const std::string& Texture::getFilename() const { return filename; }
    }
}