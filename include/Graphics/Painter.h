
#ifndef __PANCAKE__GRAPHICS__PAINTER__
#define __PANCAKE__GRAPHICS__PAINTER__


#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "../Math/Vector2.h"
#include "PainterState.h"
#include "Texture.h"
#include "OpenGL.h"
#include "Shader.h"

#define ILUT_USE_OPENGL

#include <ilut.h>


namespace Pancake {
    namespace Graphics {

        class Painter {
        private:
            PainterState currentState;
            Shader shader;
            GLuint vertexArray, elementBuffer;
            Texture texture;

        public:
            Painter();

            ~Painter();

            void initialize();

            void shutdown();

            Texture *loadTexture(const std::string &file);

            void drawQuad(const Pancake::Math::Matrix &mat);

            void drawTexture(const Pancake::Math::Matrix &mat, Pancake::Graphics::Texture *texture);

        };
    }
}

#endif