#ifndef PANCAKE_KEYBOARD
#define PANCAKE_KEYBOARD

#include <functional>
#include <SDL_scancode.h>
#include <map>
#include <SDL_system.h>

enum KeyMode {
  ONCE,
  REPEAT
};
typedef std::function<void()> Action;
typedef std::map<SDL_Scancode, Action> Actions;
typedef std::map<KeyMode, Actions> KeyboardActionMap;

class Keyboard {
private:
  KeyboardActionMap actions;

public:
  Uint8 current[SDL_NUM_SCANCODES];
  
  Uint8 previous[SDL_NUM_SCANCODES];
  
  Keyboard();
  
  void update(int delta);
  
  bool isKeyDown(SDL_Scancode scancode);
  
  bool isKeyUp(SDL_Scancode scancode);
  
  bool isKeyPressed(SDL_Scancode scancode);
  
  bool isKeyReleased(SDL_Scancode scancode);
  
  void registerKeyPress(SDL_Scancode code, Action action);
  
  void registerKeyDown(SDL_Scancode code, Action action);
};

#endif
