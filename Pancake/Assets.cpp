//
// Created by Michael Malura on 10/04/17.
//

#include "Log.h"
#include "Assets.h"

Pancake::Game::Assets::Assets() {
}

Pancake::Graphics::Texture& Pancake::Game::Assets::loadTexture(const std::string& file) {
  Log::getInstance("ASSETS")->info("Try to load texture " + file);
  
  if (textures.find(file) == textures.end()) {
    auto texture = Pancake::Graphics::Texture::loadTexture(file);
    textures[file] = texture;
  }
  return textures[file];
}

unsigned long Pancake::Game::Assets::count() {
  return textures.size();
}

void Pancake::Game::Assets::cleanup() {
  Log::getInstance("ASSETS")->info("Destroy assets");
  
  for (auto& pair : textures) {
    Log::getInstance("ASSETS")->info("Destroy texture " + (pair.second.getFilename()));
    pair.second.release();
  }
}

