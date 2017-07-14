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
  
  /**
   *
   * @param mat
   * @param texture
   */
  void drawTexture(const glm::mat4& mat, const Texture& texture);
  
  void drawSubTexture(const glm::mat4& mat, const glm::vec2& from, const glm::vec2& to, const Texture& texture);
  
  /**
   *
   * @param mat
   */
  void drawTexture(const glm::mat4& mat);
  
  /**
   *
   * @param from
   * @param to
   */
  void drawLine(const Vector2& from, const Vector2& to);
  
  /**
   *
   * @param from
   * @param size
   */
  void drawRectangle(const Vector2& from, const Vector2& size);
  
  /**
   *
   * @param from
   * @param size
   * @param color
   */
  void fillRectangle(const Vector2& from, const Vector2& size, const Color& color);
  
  void drawText(Text& text, const Vector2& position);
  
  unsigned int getDrawCalls();
};

#endif