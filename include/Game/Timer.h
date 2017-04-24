//
// Created by Michael Malura on 24/04/17.
//

#ifndef PANCAKE_TIMER_H
#define PANCAKE_TIMER_H


#include <SDL_timer.h>

namespace Pancake {
    namespace Game {
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
    }
}

#endif //PANCAKE_TIMER_H
