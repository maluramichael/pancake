
#ifndef __PANCAKE__GRAPHICS__TEXTURE__
#define __PANCAKE__GRAPHICS__TEXTURE__

#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

namespace Pancake {

    class Texture {
    private:
        int width = 0, height = 0;
        SDL_Texture *texture = nullptr;

    public:
        Texture(SDL_Texture *texture);

        ~Texture();

        SDL_Texture *getTexture() const;

        int getWidth() const;

        int getHeight() const;
    };
}

#endif