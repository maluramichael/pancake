//
// Created by Michael Malura on 10/04/17.
//

#ifndef PANCAKE_ASSETMANAGER_H
#define PANCAKE_ASSETMANAGER_H

#include <map>
#include <string>
#include "../Graphics/Texture.h"
#include "../Graphics/Painter.h"

namespace Pancake {
    namespace Game {
        class Assets {
        private:
            Graphics::Painter* painter;
            std::map<std::string, Pancake::Graphics::Texture*> textures;

        public:
            Assets(Graphics::Painter* painter);

            ~Assets();

            Graphics::Texture* loadTexture(const std::string& file);
        };
    }
}

#endif //PANCAKE_ASSETMANAGER_H
