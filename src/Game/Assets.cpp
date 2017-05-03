//
// Created by Michael Malura on 10/04/17.
//

#include "../../include/Log.h"
#include "../../include/Game/Assets.h"

Pancake::Game::Assets::Assets(Pancake::Graphics::Painter* painter) : painter(painter) {
}

Pancake::Graphics::Texture* Pancake::Game::Assets::loadTexture(const std::string& file) {
    Log::getInstance("ASSETS")->info("Try to load texture " + file);

    Pancake::Graphics::Texture* texture = nullptr;
    if (textures.find(file) == textures.end()) {
        texture = painter->loadTexture(file);
        textures[file] = texture;
    } else {
        texture = textures[file];
    }
    return texture;
}

Pancake::Game::Assets::~Assets() {
    Log::getInstance("ASSETS")->info("Destroy assets");

    for (auto pair : textures) {
        Log::getInstance("ASSETS")->info("Destroy texture " + (pair.second->getFilename()));
        delete pair.second;
    }
}

int Pancake::Game::Assets::count() {
    return textures.size();
}

