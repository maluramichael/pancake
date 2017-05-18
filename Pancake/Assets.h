//
// Created by Michael Malura on 10/04/17.
//
#pragma once
#ifndef PANCAKE_ASSETS_H
#define PANCAKE_ASSETS_H

#include <map>
#include <string>
#include "Texture.h"
#include "Painter.h"

namespace Pancake {
  namespace Game {
    class Assets {
    private:
      std::map<std::string, Pancake::Graphics::Texture> textures;
    
    public:
      Assets();
      
      void cleanup();
      
      Graphics::Texture& loadTexture(const std::string& file);
      
      unsigned long count();
    };
  }
}

#endif //PANCAKE_ASSETMANAGER_H
