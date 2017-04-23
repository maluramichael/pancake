
#ifndef __PANCAKE__GRAPHICS__PAINTER__
#define __PANCAKE__GRAPHICS__PAINTER__

#include "PainterState.h"
#include "Texture.h"

#include <SDL2/SDL_image.h>
#include <string>
#include "../Math/Vector2.h"

namespace Pancake {
    namespace Graphics {

        class Painter {
        public:
            Painter(SDL_Renderer* r);

            Texture* loadTexture(const std::string& file);

            void
            drawTexture(const Texture& texture, float x, float y, float w, float h, float ox, float oy, float rotation);

            void drawTexture(const Texture& texture, float x, float y, float w, float h, float rotation);

            void drawTexture(const Texture& texture, float x, float y, float w, float h);

            void drawTexture(const Texture& texture, float x, float y, float rotation);

            void drawTexture(const Texture& texture, float x, float y);

            void drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size, float rotation, const Math::Vector2& origin);

            void drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size, float rotation);

            void drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size);

            void drawTexture(const Texture& texture, const Math::Vector2& position);

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
            SDL_Renderer* renderer;

            PainterState currentState;
        };
    }
}

#endif