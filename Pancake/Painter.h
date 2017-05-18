#pragma once
#ifndef PANCAKE_GRAPHICS_PAINTER_H
#define PANCAKE_GRAPHICS_PAINTER_H

#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/vector_relational.hpp>

#include "Camera.h"
#include "Matrix.h"
#include "Vector2.h"
#include "Rect.h"
#include "imgui.h"
#include "PainterState.h"
#include "Texture.h"
#include "OpenGL.h"
#include "Shader.h"

namespace Pancake {
  namespace Graphics {
    
    class Painter {
    private:
      PainterState currentState;
  
      /**
       *
       */
      Shader textureShader;
  
      /**
       *
       */
      GLuint textureElementBuffer, textureVertexArray;
  
      /**
       *
       */
      Texture debugTexture;
  
      /**
       *
       */
      std::vector<VertexPositionTexture> textureVertices = {
        {0, 1, 0, 0, 1}, // top let
        {1, 1, 0, 1, 1}, // top right
        {1, 0, 0, 1, 0}, // bottom right
        {0, 0, 0, 0, 0}  // bottom let
      };
  
      /**
       *
       */
      Shader coloredQuadShader;
  
      /**
       *
       */
      GLuint coloredQuadElementBuffer, coloredQuadVertexArray;
  
      /**
       *
       */
      Texture coloredQuad;
  
      /**
       *
       */
      std::vector<VertexPosition> coloredQuadVertices = {
        {0, 1}, // top let
        {1, 1}, // top right
        {1, 0}, // bottom right
        {0, 0}  // bottom let
      };
      
      /**
       *
       */
      Shader lineShader;
      
      /**
       *
       */
      GLuint lineVertexArray, lineVertexBuffer;
      
      /**
       * 
       */
      float lineVertices[4] = {0, 0, 0.5f, 0.5f};
      
      Pancake::Math::Rect* camera;
      
      Pancake::Math::Rect* screen;
      
      void initializeColoredQuad();
      
      void initalizeTexturedQuad();
      
      void initalizeLine();
    
    public:
      Painter();
      
      Painter(Pancake::Math::Rect& camera, Math::Rect& screen);
      
      void cleanup();
      
      void initialize();
      
      void drawTexture(const glm::mat4& mat, Pancake::Graphics::Texture& texture);
      
      void drawTexture(const glm::mat4& mat);
      
      void drawLine(Pancake::Math::Vector2 from, Pancake::Math::Vector2 to);
      
      void drawRectangle(Pancake::Math::Vector2 from, Pancake::Math::Vector2 to);
      
      void fillRectangle(Pancake::Math::Vector2 from, Pancake::Math::Vector2 to);
    };
  }
}

#endif