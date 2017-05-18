//
// Created by Michael Malura on 24/04/17.
//

#include "Keyboard.h"

Pancake::Game::Keyboard::Keyboard() {
  // Get current keyboard state
  auto state = SDL_GetKeyboardState(NULL);
  
  // Initialize scancode arrays with an empty state
  memcpy(&current, state, SDL_NUM_SCANCODES);
  memcpy(&previous, state, SDL_NUM_SCANCODES);
  
  actions[KeyMode::ONCE] = Actions();
  actions[KeyMode::REPEAT] = Actions();
}

void Pancake::Game::Keyboard::update(int delta) {
  // Save current keys to the previous array for later usage
  memcpy(&previous, &current, SDL_NUM_SCANCODES);
  
  // Save current state into current array
  memcpy(&current, SDL_GetKeyboardState(NULL), SDL_NUM_SCANCODES);
  
  // Check registered event handler
  for (auto keypress : actions[KeyMode::ONCE]) {
    if (isKeyPressed(keypress.first)) {
      keypress.second();
    }
  }
  
  for (auto keydown : actions[KeyMode::REPEAT]) {
    if (isKeyDown(keydown.first)) {
      keydown.second();
    }
  }
}

bool Pancake::Game::Keyboard::isKeyDown(SDL_Scancode scancode) {
  return current[scancode] && previous[scancode];
}

bool Pancake::Game::Keyboard::isKeyUp(SDL_Scancode scancode) {
  return !current[scancode] && !previous[scancode];
}

bool Pancake::Game::Keyboard::isKeyPressed(SDL_Scancode scancode) {
  return current[scancode] && !previous[scancode];
}

bool Pancake::Game::Keyboard::isKeyReleased(SDL_Scancode scancode) {
  return !current[scancode] && previous[scancode];
}

void Pancake::Game::Keyboard::registerKeyPress(SDL_Scancode code, Pancake::Game::Action action) {
  actions[KeyMode::ONCE][code] = action;
}

void Pancake::Game::Keyboard::registerKeyDown(SDL_Scancode code, Pancake::Game::Action action) {
  actions[KeyMode::REPEAT][code] = action;
}
