#ifndef PANCAKE_ANIMATION
#define PANCAKE_ANIMATION

#include "Interpolate.h"

class Animation {
public:
  enum Mode {
    LINEAR,
    COSINE
  };
protected:
  // Parameter
  float startValue = 0.0f;
  
  float endValue = 1.0f;
  
  float duration = 1.0f;
  
  Mode mode;
  
  // Values
  float currentValue = 0.0f;
  
  float t = 0.0f;

private:
  bool running = false;
  
  bool stopped = true;
  
  bool repeat = false;
  
  bool revertOnRepeat = false;
  
  bool revert = false;

public:
  Animation(
    float startValue = 0,
    float endValue = 1,
    float duration = 1,
    bool repeat = false,
    Mode mode = LINEAR) :
    startValue(startValue),
    endValue(endValue),
    duration(duration),
    repeat(repeat),
    mode(mode) {
  }
  
  virtual void tween(float delta) {
    switch (mode) {
      case COSINE:
        currentValue = interpolateCosine(startValue, endValue, t / duration);
        break;
      case LINEAR:
        currentValue = interpolate(startValue, endValue, t / duration);
        break;
    }
  };
  
  void setStartValue(float startValue) {
    this->startValue = startValue;
  }
  
  void setEndValue(float endValue) {
    this->endValue = endValue;
  }
  
  void setDuration(float duration) {
    this->duration = duration;
  }
  
  void setMode(Mode mode) {
    this->mode = mode;
  }
  
  void setRepeat(bool repeat) {
    this->repeat = repeat;
  }
  
  void setRevertOnRepeat(bool revertOnRepeat) {
    this->revertOnRepeat = revertOnRepeat;
  }
  
  void start() {
    running = true;
    stopped = false;
  }
  
  void stop() {
    running = false;
    stopped = true;
  }
  
  bool isDone() {
    return revert ? t < 0 : t > duration;
  }
  
  void update(float delta) {
    if (!stopped) {
      if (revert) {
        if (isDone()) {
          if (repeat) {
            if (revertOnRepeat) {
              revert = false;
            } else {
              t = 1.0f;
            }
          } else {
            stop();
          }
        } else {
          t -= delta;
        }
      } else {
        if (isDone()) {
          if (repeat) {
            if (revertOnRepeat) {
              revert = true;
            } else {
              t = 0.0f;
            }
          } else {
            stop();
          }
        } else {
          t += delta;
        }
      }
    }
    
    if (running) {
      tween(delta);
    }
  }
  
  float getValue() {
    return currentValue;
  }
};

#endif
