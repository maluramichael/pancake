//
// Created by Michael Malura on 24/04/17.
//

#include "../../include/Game/Timer.h"

Pancake::Game::Timer::Timer() {}

void Pancake::Game::Timer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Pancake::Game::Timer::stop() {
    started = paused = false;
    startTicks = pausedTicks = 0;
}

void Pancake::Game::Timer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Pancake::Game::Timer::unpause() {
    if (started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Pancake::Game::Timer::getTicks() {
    Uint32 time = 0;
    if (started) {
        if (paused) {
            time = pausedTicks;
        } else {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}

bool Pancake::Game::Timer::isStarted() {
    return started;
}

bool Pancake::Game::Timer::isPaused() {
    return paused;
}
