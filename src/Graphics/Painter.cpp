//
// Created by Michael Malura on 22/11/16.
//

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../include/Graphics/Painter.h"
#include "../../include/Log.h"


namespace Pancake {
    namespace Graphics {

        Painter::Painter(SDL_Renderer* r) : renderer(r) {}

        Texture* Painter::loadTexture(const std::string& file) {
            std::cout << "Load texture: " << file << std::endl;
            auto sdlTexture = IMG_LoadTexture(this->renderer, file.c_str());
            if (sdlTexture == nullptr) {
                Pancake::logSDLError(std::cout, "LoadTexture");
            }

            auto texture = new Texture(sdlTexture);
            texture->setFilename(file);

            return texture;
        }

        void Painter::drawTexture(Texture* texture, float x, float y, float w, float h, float sx, float sy, float sw,
                                  float sh) {}

        void Painter::drawTexture(const Texture& texture, float x, float y, float w,
                                  float h) {
            SDL_Rect destination;
            destination.x = x;
            destination.y = y;
            destination.w = w;
            destination.h = h;
            SDL_RenderCopy(this->renderer, texture.getTexture(), nullptr, &destination);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y) {
            drawTexture(texture, x, y, texture.getWidth(), texture.getHeight());
        }

        void Painter::drawTexture(const Texture& texture) {
            drawTexture(texture, 0, 0);
        }

        void Painter::drawLine(float x0, float y0, float x1, float y1) {
            auto color = this->currentState.getColor();
            aalineRGBA(this->renderer, x0, y0, x1, y1, color.red(), color.green(), color.blue(), color.alpha());
            // SDL_RenderDrawLine(this->renderer,x0, y0, x1, y1);
        }

        void Painter::saveState() { currentState = PainterState(); }

        void Painter::restoreState() {
            auto color = this->currentState.getColor();
            SDL_SetRenderDrawColor(this->renderer, color.red(), color.green(), color.blue(), color.alpha());
        }

        void Painter::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            currentState.setColor((r << 24) | (g << 16) | (b << 8) | (a));
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
        }

        void Painter::drawRectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h) {
            boxColor(renderer, x, y, x + w, y + h, currentState.getColor().getColor());
        }

        void Painter::drawPixel(Sint16 x, Sint16 y) {
            pixelColor(renderer, x, y, currentState.getColor().getColor());
        }

        void Painter::drawRectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h, int color) {
            boxColor(renderer, x, y, x + w, y + h, color);
        }

        void Painter::drawPixel(Sint16 x, Sint16 y, int color) {
            pixelColor(renderer, x, y, color);
        }

        void Painter::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            setColor(r, g, b, a);
            SDL_RenderClear(renderer);
        }

    }
}