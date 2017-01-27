
#ifndef __PANCAKE__GRAPHICS__PAINTER__
#define __PANCAKE__GRAPHICS__PAINTER__

#include "PainterState.h"
#include "Texture.h"

#include <SDL2/SDL_image.h>
#include <string>

namespace Pancake {

    class Painter {
    public:
        Painter(SDL_Renderer *r);

        SDL_Texture *loadTexture(const std::string &file);

        void drawTexture(Texture *texture, float x, float y, float w, float h, float sx, float sy, float sw, float sh);

        void drawTexture(const Texture &texture, float x, float y, float w, float h);

        void drawTexture(const Texture &texture, float x, float y);

        void drawTexture(const Texture &texture);

        void drawLine(float x0, float y0, float x1, float y1);

        void drawPixel(Sint16 x, Sint16 y);

        void drawPixel(Sint16 x, Sint16 y, int color);

        void drawRectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        void drawRectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h, int color);

        void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        void saveState();

        void restoreState();

    private:
        SDL_Renderer *renderer;
        PainterState currentState;
    };
}

#endif