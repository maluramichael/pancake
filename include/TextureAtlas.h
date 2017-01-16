//
// Created by Michael Malura on 17/11/16.
//

#ifndef GAME_TEXTUREATLAS_H
#define GAME_TEXTUREATLAS_H

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <vector>

namespace Pancake {

    class TextureAtlas {
    private:
        std::vector<SDL_Rect> rects;

    public:
        TextureAtlas(std::string path);

        SDL_Rect &addSprite(int x, int y, int w, int h);

        SDL_Rect &getSprite(int index);

        SDL_Rect &operator[](int x);
    };

}

#endif //GAME_TEXTUREATLAS_H
