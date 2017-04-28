//
// Created by Michael Malura on 27/01/17.
//

#include <imgui.h>

#include "../../include/Game/Game.h"
#include "../../include/UI/imgui_impl_sdl_gl3.h"

int Pancake::Game::Game::init() {
    Pancake::Log::initialize();
    Pancake::LogHandle log = Pancake::Log::getInstance("GAME");

    beforeSDLInitialized();
    log->info("Initialize sdl");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        log->error(SDL_GetError());
        return Pancake::Codes::ERROR;
    }
    afterSDLInitialized();

    log->info("Initialize sdl image");
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        log->error(SDL_GetError());
        SDL_Quit();
        return Pancake::Codes::ERROR;
    }

    beforeWindowCreated();
    log->info("Create window");
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int) resolution.x,
                              (int) resolution.y, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        log->error(SDL_GetError());
        SDL_Quit();
        return Pancake::Codes::ERROR;
    }
    afterWindowCreated();

    beforeRendererCreated();
    log->info("Create renderer");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        log->error(SDL_GetError());
        Pancake::cleanup(window);
        SDL_Quit();
        return Pancake::Codes::ERROR;
    }
    afterRendererCreated();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    beforeOpenGLContextCreated();
    glContext = SDL_GL_CreateContext(this->window);
    afterOpenGLContextCreated();

    beforeGLEWInit();
    if (GLEW_OK != glewInit()) {
        log->error("Could not initialize glew");
        return Pancake::Codes::ERROR;
    }
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    afterGLEWInit();

    log->info("Create painter");
    painter = new Pancake::Graphics::Painter(renderer);

    log->info("Create asset manager");
    assets = new Pancake::Game::Assets(painter);

    log->info("Load assets");
    loadAssets();

    log->info("Register default keyboard actions");
    keyboard.registerKeyPress(SDL_SCANCODE_ESCAPE, std::bind(&Pancake::Game::Game::quitGame, this));
    keyboard.registerKeyPress(SDL_SCANCODE_F8, [this] {
        this->setFullscreen(Pancake::Game::Game::WindowMode::WINDOWED);
    });
    keyboard.registerKeyPress(SDL_SCANCODE_F9, [this] {
        this->setFullscreen(Pancake::Game::Game::WindowMode::FULLSCREEN_WINDOWED);
    });
    keyboard.registerKeyPress(SDL_SCANCODE_F10, [this] {
        this->debug = !this->debug;
    });

    log->info("Game initialized");
    initialized();

    log->info("Initialize imgui");
    ImGui_ImplSdlGL3_Init(window);

    return Pancake::Codes::OK;
}

void Pancake::Game::Game::destroy() {
    Pancake::LogHandle log = Pancake::Log::getInstance("GAME");

    log->info("Shutdown imgui");
    ImGui_ImplSdlGL3_Shutdown();

    beforeDestroy();

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
    destroyed();

    log->info("Done destroying game");
    Pancake::Log::release();
}

Pancake::Game::Game::Game(std::string title, int width, int height) {
    setResolution(width, height);
    setTitle(title);
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
    do {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            processEvent(&event);
            // System events
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            ImGui_ImplSdlGL3_ProcessEvent(&event);
        }
        keyboard.update(0);

        float delta = timer.getTicks() / 1000.0f;
        update(delta);
        if (debug) { updateUI(delta); }
        timer.start(); // restart time for next frame

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();
        if (debug) { ImGui::Render(); }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);

        renderUI();
    } while (!quit);

    log->info("Quit game");
    destroy();
}

void Pancake::Game::Game::quitGame() {
    quit = true;
}

void Pancake::Game::Game::setTitle(std::string title) {
    this->title = title;
    SDL_SetWindowTitle(this->window, title.c_str());
}

void Pancake::Game::Game::setResolution(int width, int height) {
    this->resolution = Pancake::Math::Vector2(width, height);
    SDL_SetWindowSize(this->window, width, height);
}

void Pancake::Game::Game::setFullscreen(WindowMode mode) {
    this->windowMode = mode;
    SDL_SetWindowFullscreen(this->window, mode);

    int w, h;
    SDL_GetWindowSize(this->window, &w, &h);
    this->resolution = Pancake::Math::Vector2(w, h);
}