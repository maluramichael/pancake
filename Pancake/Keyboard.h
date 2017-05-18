//
// Created by Michael Malura on 24/04/17.
//

#pragma once
#ifndef PANCAKE_KEYBOARD_H
#define PANCAKE_KEYBOARD_H

#include <functional>
#include <SDL_scancode.h>
#include <map>
#include <SDL_system.h>

namespace Pancake {
    namespace Game {
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
    }
}

#endif //PANCAKE_KEYBOARD_H
