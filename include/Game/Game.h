//
// Created by Michael Malura on 27/01/17.
//

#ifndef PANCAKE_GAME_H
#define PANCAKE_GAME_H

#include <GL/glew.h>

#include "Assets.h"
#include "Keyboard.h"
#include "Timer.h"
#include "Camera.h"
#include "../Constants.h"
#include "../Log.h"
#include "../Cleanup.h"
#include "../Graphics/Painter.h"

namespace Pancake {
    namespace Game {
        class Game {
        public:
            enum WindowMode {
                WINDOWED = 0,
                FULLSCREEN = SDL_WINDOW_FULLSCREEN,
                FULLSCREEN_WINDOWED = SDL_WINDOW_FULLSCREEN_DESKTOP
            };

            Game(std::string title = "Game", int width = 640, int height = 480);

            void run();

            void quitGame();

            void setTitle(std::string title);

            void setResolution(int width, int height);

            void setFullscreen(WindowMode mode);


        protected:
            Pancake::Game::Camera camera;
            Pancake::Graphics::Painter* painter = nullptr;
            Pancake::Game::Assets* assets = nullptr;
            Keyboard keyboard;

            SDL_Window* window = nullptr;
            SDL_Renderer* renderer = nullptr;
            SDL_GLContext glContext = nullptr;

        private:
            bool quit = false;
            std::string title = "";
            WindowMode windowMode = WINDOWED;
            Pancake::Math::Vector2 resolution;

            int init();

            void destroy();

            virtual void beforeInit() {}

            virtual void afterInit() {}

            virtual void loadAssets() {}

            virtual void destroyAssets() {}

            virtual void afterDestroy() {}

            virtual void update(float delta) {}

            virtual void render() {}

            virtual void setupSDLOpenGL();

            virtual void afterOpenGL() {};

            virtual void processEvent(SDL_Event* event) {
            }

        };
    }
}

#endif //PANCAKE_GAME_H
