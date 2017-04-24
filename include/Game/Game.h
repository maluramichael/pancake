//
// Created by Michael Malura on 27/01/17.
//

#ifndef PANCAKE_GAME_H
#define PANCAKE_GAME_H

#include "../Graphics/Painter.h"
#include "Assets.h"
#include "Keyboard.h"
#include "Timer.h"
#include "../Constants.h"
#include "../Log.h"
#include "../Cleanup.h"

namespace Pancake {
    namespace Game {
        class Game {
        protected:
            Pancake::Graphics::Painter* painter = nullptr;
            Pancake::Game::Assets* assets = nullptr;
            Keyboard keyboard;

        private:
            bool quit = false;
            std::string title = "";
            int width = 0, height = 0;

            SDL_Window* window = nullptr;
            SDL_Renderer* renderer = nullptr;

            int init();

            void destroy();

            virtual void beforeInit() {}

            virtual void afterInit() {}

            virtual void loadAssets() {}

            virtual void destroyAssets() {}

            virtual void afterDestroy() {}

            virtual void update(float delta) {}

            virtual void render() {}

        public:
            Game(std::string title = "Game", int width = 640, int height = 480);

            void run();

            void quitGame();
        };
    }
}

#endif //PANCAKE_GAME_H
