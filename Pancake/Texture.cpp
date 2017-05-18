//
// Created by Michael Malura on 22/11/16.
//

#include "Texture.h"

namespace Pancake {
    namespace Graphics {

        Texture Texture::loadTexture(const std::string& file) {

            int x, y, n;
            unsigned char* data = stbi_load(file.c_str(), &x, &y, &n, 0);

            GLenum format;

            switch (n) {
                case 1:
                    format = GL_ALPHA;
                case 2:
                    format = GL_ALPHA;
                case 3:
                    format = GL_RGB;
                case 4:
                default:
                    format = GL_RGBA;
            }

            GLuint glID = 0;
            glGenTextures(1, &glID);

            std::cout << "Generate texture " << glID << " from " << file << "\n";

            glBindTexture(GL_TEXTURE_2D, glID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0, format, GL_UNSIGNED_BYTE, data);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(data);

            Texture texture(glID);
            texture.setFilename(file);
            texture.setDimensions({x, y});
            return texture;
        }

        Texture::Texture() {
        }

        Texture::Texture(GLuint id) : id(id) {
        }

        void Texture::release() {
            if (id != 0) glDeleteTextures(1, &id);
        }

        void Texture::begin() {
            glBindTexture(GL_TEXTURE_2D, id);
        }

        void Texture::end() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void Texture::generate() {
            if (id != 0) return;
            id = 0;
            glGenTextures(1, &id);
            std::cout << "Generate texture " << id << "\n";
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
                    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
            };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
            end();
        }


        Texture::~Texture() {
            if (id != 0) glDeleteTextures(1, &id);
        }

        void Texture::setFilename(const std::string& filename) { Texture::filename = filename; }

        const std::string& Texture::getFilename() const { return filename; }

        const Math::Vector2& Texture::getDimensions() const {
            return dimensions;
        }

        void Texture::setDimensions(Math::Vector2 dimensions) {
            Texture::dimensions = dimensions;
        }
    }
}