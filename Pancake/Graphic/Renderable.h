#ifndef PANCAKE_RENDERABLE
#define PANCAKE_RENDERABLE

#include <glm/vec3.hpp>

class Renderable {
protected:
  glm::vec3 position, size = glm::vec3(1), rotation;

public:
//      virtual void render(const Painter& painter) = 0;
};

#endif
