
#ifndef __PANCAKE__GRAPHICS__PAINTER__
#define __PANCAKE__GRAPHICS__PAINTER__

#include "PainterState.h"
#include "Texture.h"

#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "../Math/Vector2.h"
#include "OpenGL.h"
#include "Shader.h"

namespace Pancake {
    namespace Graphics {

        class Painter {
        private:
            SDL_Renderer* renderer;
            PainterState currentState;
            Shader shader;
            GLuint vertexArray, elementBuffer;
            Texture texture;

        public:
            Painter(SDL_Renderer* r);

            void initialize();

            Texture* loadTexture(const std::string& file);

            void drawTexture(const Texture& texture,
                             float x, float y,
                             float w, float h,
                             float ox, float oy,
                             float rotation);

            void drawTexture(const Texture& texture, float x, float y, float w, float h, float rotation);

            void drawTexture(const Texture& texture, float x, float y, float w, float h);

            void drawTexture(const Texture& texture, float x, float y, float rotation);

            void drawTexture(const Texture& texture, float x, float y);

            void drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size,
                             float rotation, const Math::Vector2& origin);

            void drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size,
                             float rotation);

            void drawTexture(const Texture& texture, const Math::Vector2& position, const Math::Vector2& size);

            void drawTexture(const Texture& texture, const Math::Vector2& position);

            void drawTexture(const Texture& texture);

            void drawRawTexture(SDL_Texture* texture);

            void drawLine(float x0, float y0, float x1, float y1);

            void drawLine(const Math::Vector2& from, const Math::Vector2& to);

            void drawPixel(float x, float y);

            void drawPixel(const Math::Vector2& position);

            void drawPixel(float x, float y, int color);

            void drawRectangle(float x, float y, float w, float h);

            void drawRectangle(const Math::Vector2& position, const Math::Vector2& size);

            void drawRectangle(float x, float y, float w, float h, int color);

            void drawQuad(float x = 0, float y = 0);

            void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void saveState();

            void restoreState();

            SDL_Renderer* getRenderer() const;


        };
    }
}

#endif