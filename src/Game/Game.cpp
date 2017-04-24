//
// Created by Michael Malura on 27/01/17.
//

#include "../../include/Game/Game.h"

int Pancake::Game::Game::init() {
    Pancake::Log::initialize();
    Pancake::LogHandle log = Pancake::Log::getInstance("GAME");

    beforeInit();

    log->info("Initialize sdl");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        log->error(SDL_GetError());
        return Pancake::Codes::ERROR;
    }

    log->info("Initialize sdl image");
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        log->error(SDL_GetError());
        SDL_Quit();
        return Pancake::Codes::ERROR;
    }

    log->info("Create window");
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        log->error(SDL_GetError());
        SDL_Quit();
        return Pancake::Codes::ERROR;
    }

    log->info("Create renderer");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        log->error(SDL_GetError());
        Pancake::cleanup(window);
        SDL_Quit();
        return Pancake::Codes::ERROR;
    }

    log->info("Create painter");
    painter = new Pancake::Graphics::Painter(renderer);

    log->info("Create asset manager");
    assets = new Pancake::Game::Assets(painter);

    log->info("Load assets");
    loadAssets();

    log->info("Game initialized");
    afterInit();
    return Pancake::Codes::OK;
}

void Pancake::Game::Game::destroy() {
    Pancake::LogHandle log = Pancake::Log::getInstance("GAME");

    log->info("Destroy assets");
    destroyAssets();

    log->info("Delete asset manager");
    delete assets;
    assets = nullptr;

    log->info("Delete painter");
    delete painter;
    painter = nullptr;

    log->info("Cleanup renderer and window");
    Pancake::cleanup(renderer, window);

    renderer = nullptr;
    window = nullptr;

    log->info("Quit sdl image");
    IMG_Quit();

    log->info("Quit sdl");
    SDL_Quit();

    log->info("Destroy everything else");
    afterDestroy();

    log->info("Done destroying game");
    Pancake::Log::release();
}

Pancake::Game::Game::Game(std::string title, int width, int height) : title(title), width(width),
                                                                      height(height) {
}

void Pancake::Game::Game::run() {
    if (init() != Pancake::Codes::OK) {
        return;
    }

    Timer timer;
    Pancake::LogHandle log = Pancake::Log::getInstance("GAME");
    log->info("Run game");
    /**
     * GAME LOOP
     */
    while (!quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            // System events
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        keyboard.update(0);
        painter->clear(50, 50, 50, 255);

        float delta = timer.getTicks() / 1000.0f;
        update(delta);
        timer.start(); // restart time for next frame

        render();
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    log->info("Quit game");
    destroy();
}

void Pancake::Game::Game::quitGame() {
    quit = true;
}
