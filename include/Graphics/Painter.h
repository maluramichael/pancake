
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

#include "../Game/Camera.h"
#include "../Math/Matrix.h"
#include "../Math/Vector2.h"
#include "../Math/Rect.h"
#include "PainterState.h"
#include "Texture.h"
#include "OpenGL.h"
#include "Shader.h"


namespace Pancake {
    namespace Graphics {

        class Painter {
        private:
            PainterState currentState;

            // Quad
            Shader quadShader;
            GLuint quadElementBuffer, quadVertexArray;
            Texture texture;
            std::vector<VertexPositionTexture> quadVertices = {
                    {0, 1, 0, 0, 1}, // top let
                    {1, 1, 0, 1, 1}, // top right
                    {1, 0, 0, 1, 0}, // bottom right
                    {0, 0, 0, 0, 0}  // bottom let
            };

            // Line
            Shader lineShader;
            GLuint lineVertexArray, lineVertexBuffer;
            float lineVertices[4] = {0, 0, 0.5f, 0.5f};

            Pancake::Game::Camera& camera;
            Pancake::Math::Rect& screen;

            void initalizeQuad();

            void initalizeLine();

        public:
            Painter(Pancake::Game::Camera& camera, Math::Rect& screen);

            ~Painter();

            void initialize();

            void shutdown();

            Texture* loadTexture(const std::string& file);

            void drawQuad(const Pancake::Math::Matrix& mat);

            void drawTexture(const glm::mat4& mat, Pancake::Graphics::Texture* texture);

            void drawTexture(const glm::mat4& mat);

            void drawLine(Pancake::Math::Vector2 from, Pancake::Math::Vector2 to);


        };
    }
}

#endif