#include "Painter.h"

Painter::Painter(Rect& camera, Rect& screen) : camera(&camera), screen(&screen) {
}

//void Painter::initalizeLine() {
//  glGenBuffers(1, &lineVertexBuffer);
//  glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);
//
//  // Line shader
//  std::string vertexShader = "#version 150\n"
//    "\n"
//    "uniform mat4 mat;\n"
//    "in vec2 position;\n"
//    "\n"
//    "void main()\n"
//    "{\n"
//    "    gl_Position = mat * vec4(position, 0.0, 1.0);\n"
//    "}";
//  std::string fragmentShader = "#version 150\n"
//    "\n"
//    "out vec4 outColor;\n"
//    "\n"
//    "void main()\n"
//    "{\n"
//    "    outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
//    "}";
//
//  //lineShader.setFragmentShaderSource(fragmentShader);
//  //lineShader.setVertexShaderSource(vertexShader);
//  lineShader.load();
//  lineShader.loadUniforms(std::vector<std::string>{"mat"});
//  lineShader.begin();
//
//  auto program = lineShader.getProgram();
//  lineVertexArray = createVertexArray();
//  glBindVertexArray(lineVertexArray);
//
//  auto positionAttribute = createVertexAttributePointer(program,
//                                                        "position",
//                                                        2,
//                                                        GL_FLOAT,
//                                                        0,
//                                                        0);
//  glEnableVertexAttribArray(positionAttribute);
//  lineShader.end();
//}

void Painter::initalizeTexturedQuad() {
  
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColor) * textureVertices.size(), &textureVertices[0],
               GL_STATIC_DRAW);
  
  subTextureShader = new SubTextureShader(File("res/shader/subTexture.vs"), File("res/shader/subTexture.fs"));
  subTextureShader->initialize();
  subTextureShader->begin();
  
  //textureShader.initialize();
  //textureShader.begin();
  
  GLuint elements[] = { // clock wise 2 triangles
    0, 1, 2, // top left, top right, bottom right
    0, 2, 3 // top left, bottom right, bottom left
  };
  
  //glBindVertexArray(subTextureShader->vertexArray);
  textureElementBuffer = createBuffer();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureElementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  
  //textureShader.end();
  subTextureShader->end();
  
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

//void Painter::initializeColoredQuad() {
//  GLuint vertexBuffer;
//  glGenBuffers(1, &vertexBuffer);
//  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPosition) * coloredQuadVertices.size(), &coloredQuadVertices[0], GL_STATIC_DRAW);
//
//  std::string vertexShader = "#version 150\n"
//    "\n"
//    "uniform mat4 mat;\n"
//    "uniform vec4 col;\n"
//    "in vec2 position;\n"
//    "out vec4 color;\n"
//    "\n"
//    "void main()\n"
//    "{\n"
//    "    color = col;\n"
//    "    gl_Position = mat * vec4(position, 0.0, 1.0);\n"
//    "}";
//  std::string fragmentShader = "#version 150\n"
//    "\n"
//    "out vec4 outColor;\n"
//    "in vec4 color;\n"
//    "\n"
//    "void main()\n"
//    "{\n"
//    "    outColor = color;//vec4(1.0, 1.0, 1.0, 1.0);\n"
//    "}";
//
//  //coloredQuadShader.setFragmentShaderSource(fragmentShader);
//  //coloredQuadShader.setVertexShaderSource(vertexShader);
//  coloredQuadShader.load();
//  coloredQuadShader.loadUniforms(std::vector<std::string>{"mat", "col"});
//  coloredQuadShader.begin();
//
//  auto program = coloredQuadShader.getProgram();
//  coloredQuadVertexArray = createVertexArray();
//  glBindVertexArray(coloredQuadVertexArray);
//
//  auto positionAttribute = createVertexAttributePointer(program, "position", 2, GL_FLOAT, 2 * sizeof(float), 0);
//  glEnableVertexAttribArray(positionAttribute);
//
//  GLuint elements[] = { // clock wise 2 triangles
//    0, 1, 2, // top left, top right, bottom right
//    0, 2, 3 // top left, bottom right, bottom left
//  };
//
//  coloredQuadElementBuffer = createBuffer();
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, coloredQuadElementBuffer);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
//
//  coloredQuadShader.end();
//
//  glBindVertexArray(0);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//  glUseProgram(0);
//}

void Painter::initialize() {
  debugTexture.generate();
  
  this->initalizeTexturedQuad();
  //this->initializeColoredQuad();
  //this->initalizeLine();

//      short indices[2] = {0, 1};
//      float vertices[4] = {0, 0, 100, 100};
//      line.setIndices(indices, 2);
//      line.setVertices(vertices, sizeof(float) * 4);
}

void Painter::drawTexture(const glm::mat4& mat, const Texture& texture) {
  //glBindVertexArray(textureVertexArray);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureElementBuffer);
  //
  //glm::mat4 projection = glm::ortho(0.0f, screen->w, screen->h, 0.0f, -5.0f, 5.0f);
  //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->x, -camera->y, 0));
  //auto mvp = projection * view * mat;
  //
  //textureShader.begin();
  //textureShader.set("mat", glm::value_ptr(mvp));
  //
  //texture.begin();
  //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //drawCalls++;
  //texture.end();
  //
  //glBindVertexArray(0);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //textureShader.end();
}

void Painter::drawText(Text& text, const Vector2& position) {
  
  //float x, y;
  //const char* c = text.text;
  //for (int i = 0; i < 2; i++) {
  //stbtt_aligned_quad q;
  //auto model = glm::translate(glm::mat4(), glm::vec3(position.x, position.y, 0.0f));
  //auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 20.0f, 1.0f));
  //model = model * scale;
  
  //drawSubTexture(model, {0, 0}, {256, 256}, text.font->texture);
  //glTexCoord2f(q.s0,q.t1); glVertex2f(q.x0,q.y0);
  //glTexCoord2f(q.s1,q.t1); glVertex2f(q.x1,q.y0);
  //glTexCoord2f(q.s1,q.t0); glVertex2f(q.x1,q.y1);
  //glTexCoord2f(q.s0,q.t0); glVertex2f(q.x0,q.y1);
  //}
}

void Painter::drawSubTexture(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& from, const glm::vec2& to, const Texture& texture) {
  
  auto modelMat = glm::translate(glm::mat4(), glm::vec3(position.x, position.y, 0.0f));
  auto scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x * texture.dimensions.x, scale.y * texture.dimensions.y, 1.0f));
  modelMat = modelMat * scaleMat;
  
  glBindVertexArray(subTextureShader->vertexArray);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureElementBuffer);
  
  glm::mat4 projection = glm::ortho(0.0f, screen->w, screen->h, 0.0f, -5.0f, 5.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->x, -camera->y, 0));
  auto mvp = projection * view * modelMat;
  
  subTextureShader->begin();
  subTextureShader->set("mat", glm::value_ptr(mvp));
  subTextureShader->set("dimensions", texture.dimensions.x, texture.dimensions.y);
  subTextureShader->set("from", from.x, from.y);
  subTextureShader->set("to", to.x, to.y);
  
  texture.begin();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  drawCalls++;
  texture.end();
  
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  subTextureShader->end();
}

void Painter::drawTexture(const glm::mat4& mat) {
  drawTexture(mat, debugTexture);
}

void Painter::drawLine(const Vector2& from, const Vector2& to) {
  
  //glm::mat4 projection = glm::ortho(0.0f, screen->w, screen->h, 0.0f, -5.0f, 5.0f);
  //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->x, -camera->y, 0));
  //auto mvp = projection * view;
  //
  //lineVertices[0] = from.x;
  //lineVertices[1] = from.y;
  //lineVertices[2] = to.x;
  //lineVertices[3] = to.y;
  //
  //glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
  //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVertices), lineVertices);
  //glBindVertexArray(lineVertexArray);
  //
  //lineShader.begin();
  //lineShader.set("mat", glm::value_ptr(mvp));
  //
  //glDrawArrays(GL_LINES, 0, 2);
  //drawCalls++;
  //
  //lineShader.end();
  //glBindVertexArray(0);
}

void Painter::cleanup() {
  debugTexture.release();
  //coloredQuadShader.release();
  //lineShader.release();
  //textureShader.release();
  
  if (subTextureShader != nullptr) {
    subTextureShader->release();
    delete subTextureShader;
  }
  
}

void Painter::drawRectangle(const Vector2& from, const Vector2& size) {
}

void Painter::fillRectangle(const Vector2& from, const Vector2& size, const Color& color) {
  //glBindVertexArray(coloredQuadVertexArray);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, coloredQuadElementBuffer);
  //
  //glm::mat4 projection = glm::ortho(0.0f, screen->w, screen->h, 0.0f, -5.0f, 5.0f);
  //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->x, -camera->y, 0));
  //glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(from.x, from.y, 0));
  //glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1));
  //glm::mat4 mat = translation * scale;
  //auto mvp = projection * view * mat;
  //
  //coloredQuadShader.begin();
  //coloredQuadShader.set("mat", glm::value_ptr(mvp));
  //coloredQuadShader.set("col", color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0f);
  //
  //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //drawCalls++;
  //
  //glBindVertexArray(0);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //coloredQuadShader.end();
}

unsigned int Painter::getDrawCalls() {
  auto tempDrawCalls = drawCalls;
  drawCalls = 0;
  return tempDrawCalls;
}

void Painter::reloadShader() {
  //textureShader.reload();
  subTextureShader->reload();
}
