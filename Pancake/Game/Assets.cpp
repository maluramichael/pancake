#include "Log.h"
#include "Assets.h"

Assets::Assets() {
}

Texture& Assets::loadTexture(const std::string& file) {
  Log::getInstance("ASSETS")->info("Try to load texture " + file);
  
  if (textures.find(file) == textures.end()) {
    auto texture = Texture::loadTexture(file);
    textures[file] = texture;
  }
  return textures[file];
}

unsigned long Assets::count() {
  return textures.size();
}

void Assets::cleanup() {
  Log::getInstance("ASSETS")->info("Destroy assets");
  
  for (auto& pair : textures) {
    Log::getInstance("ASSETS")->info("Destroy texture " + (pair.second.getFilename()));
    pair.second.release();
  }
}

