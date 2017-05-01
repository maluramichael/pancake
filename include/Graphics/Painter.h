
#ifndef __PANCAKE__GRAPHICS__PAINTER__
#define __PANCAKE__GRAPHICS__PAINTER__


#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/vector_relational.hpp>

#include "../Math/Matrix.h"
#include "../Math/Vector2.h"
#include "PainterState.h"
#include "Texture.h"
#include "OpenGL.h"
#include "Shader.h"


namespace Pancake {
    namespace Graphics {

        class Painter {
        private:
            PainterState currentState;
            Shader shader;
            GLuint vertexArray, elementBuffer;
            Texture texture;
            glm::mat4 view;

        public:
            Painter();

            ~Painter();

            void initialize();

            void shutdown();

            Texture* loadTexture(const std::string& file);

            void drawQuad(const Pancake::Math::Matrix& mat);

            void drawTexture(const Pancake::Math::Matrix& mat, Pancake::Graphics::Texture* texture);

            void drawTexture(const glm::mat4& mat, Pancake::Graphics::Texture* texture);

        };
    }
}

#endif