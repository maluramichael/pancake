#ifndef PANCAKE_TIMER
#define PANCAKE_TIMER

#include <SDL_timer.h>

class Timer {
public:
  Timer();
  
  void start();
  
  void stop();
  
  void pause();
  
  void unpause();
  
  Uint32 getTicks();
  
  bool isStarted();
  
  bool isPaused();

private:
  Uint32 startTicks = 0, pausedTicks = 0;
  
  bool paused = false, started = false;
};

#endif
