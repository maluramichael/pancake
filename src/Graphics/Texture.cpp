//
// Created by Michael Malura on 22/11/16.
//

#include "../../include/Graphics/Texture.h"

namespace Pancake {

Texture::Texture(SDL_Texture *texture) : texture(texture) {
  if (texture != nullptr) {
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    std::cout << "Width: " << width << " Height: " << height << std::endl;
  }
}

Texture::~Texture() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }
}

SDL_Texture *Texture::getTexture() const { return texture; }

int Texture::getWidth() const { return this->width; }

int Texture::getHeight() const { return this->height; }
}