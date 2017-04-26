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

        void Painter::drawTexture(const Texture& texture, float x, float y, float w, float h, float ox, float oy,
                                  float rotation) {
            SDL_Rect destination;
            destination.x = x;
            destination.y = y;
            destination.w = w;
            destination.h = h;

            SDL_Point offset;
            offset.x = ox;
            offset.y = oy;

            SDL_RenderCopyEx(this->renderer, texture.getTexture(), nullptr, &destination, rotation, &offset,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y, float w, float h, float rotation) {
            drawTexture(texture, x, y, w, h, 0, 0, rotation);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y, float w, float h) {
            drawTexture(texture, x, y, w, h, 0);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y, float roation) {
            drawTexture(texture, x, y, texture.getDimensions().x, texture.getDimensions().y, roation);
        }

        void Painter::drawTexture(const Texture& texture, float x, float y) {
            drawTexture(texture, x, y, 0);
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

        void Painter::drawRectangle(float x, float y, float w, float h) {
            boxColor(renderer, x, y, x + w, y + h, currentState.getColor().getColor());
        }

        void Painter::drawPixel(float x, float y) {
            pixelColor(renderer, x, y, currentState.getColor().getColor());
        }

        void Painter::drawRectangle(float x, float y, float w, float h, int color) {
            boxColor(renderer, x, y, x + w, y + h, color);
        }

        void Painter::drawPixel(float x, float y, int color) {
            pixelColor(renderer, x, y, color);
        }

        void Painter::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            setColor(r, g, b, a);
            SDL_RenderClear(renderer);
        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position) {
            drawTexture(texture, position, Math::Vector2(1, 1));
        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size) {
            drawTexture(texture, position, size, 0);
        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size,
                                  float rotation) {
            drawTexture(texture, position, size, rotation, Math::Vector2(0, 0));

        }

        void Painter::drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size,
                                  float rotation, const Math::Vector2& origin) {
            float w = texture.getDimensions().x * size.x;
            float h = texture.getDimensions().y * size.y;

            SDL_Point offset;
            offset.x = origin.x * w;
            offset.y = origin.y * h;

            SDL_Rect destination;
            destination.x = position.x - offset.x;
            destination.y = position.y - offset.y;
            destination.w = w;
            destination.h = h;


            SDL_RenderCopyEx(this->renderer, texture.getTexture(), nullptr, &destination, rotation, &offset,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

        void Painter::drawTexture(const Texture& texture) {

        }

        void Painter::drawLine(const Math::Vector2& from, const Math::Vector2& to) {
            drawLine(from.x, from.y, to.x, to.y);
        }

        void Painter::drawPixel(const Math::Vector2& position) {
            drawPixel(position.x, position.y);
        }

        void Painter::drawRectangle(const Math::Vector2& position, const Math::Vector2& size) {
            drawRectangle(position.x, position.y, size.x, size.y);
        }

        void Painter::drawRawTexture(SDL_Texture* texture) {
            SDL_Rect destination;
            destination.x = 0;
            destination.y = 0;

            Uint32 format;
            int access;
            int w;
            int h;
            SDL_QueryTexture(texture, &format, &access, &w, &h);
            destination.w = w;
            destination.h = h;


            SDL_RenderCopy(this->renderer, texture, nullptr, &destination);
        }

        SDL_Renderer* Painter::getRenderer() const {
            return renderer;
        }

    }
}