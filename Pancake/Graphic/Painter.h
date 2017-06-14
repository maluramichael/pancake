#ifndef PANCAKE_GRAPHICS_PAINTER
#define PANCAKE_GRAPHICS_PAINTER

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
#include "../Game/Log.h"
#include "../Math/Matrix.h"
#include "../Math/Vector2.h"
#include "../Math/Rect.h"
#include "../UI/imgui.h"
#include "PainterState.h"
#include "Texture.h"
#include "OpenGL.h"
#include "Shader.h"
#include "TextureShader.h"
#include "Mesh.h"
#include "Text.h"

class Painter {
private:
  unsigned int drawCalls = 0;
  
  PainterState currentState;
  
  Mesh quad, line;
  
  /**
   *
   */
  TextureShader textureShader;
  
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
  
  Rect* camera;
  
  Rect* screen;
  
  void initializeColoredQuad();
  
  void initalizeTexturedQuad();
  
  void initalizeLine();

public:
  Painter();
  
  Painter(Rect& camera, Rect& screen);
  
  void cleanup();
  
  void initialize();
  
  void drawTexture(const glm::mat4& mat, Texture& texture);
  
  void drawTexture(const glm::mat4& mat);
  
  void drawLine(Vector2 from, Vector2 to);
  
  void drawRectangle(Vector2 from, Vector2 size);
  
  void fillRectangle(Vector2 from, Vector2 size, Color color);
  
  unsigned int getDrawCalls();
};

#endif