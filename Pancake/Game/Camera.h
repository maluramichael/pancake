#ifndef PANCAKE_CAMERA
#define PANCAKE_CAMERA

#include "../Math/Rect.h"
#include "../Math/Vector2.h"

class Camera : public Rect {
public:
  Camera() : Rect(Vector2(0, 0), Vector2(100, 100)) {
  }
};

#endif
