//
// Created by Michael Malura on 27/01/17.
//

// pancake
#include "BaseGame.h"

int Pancake::Game::BaseGame::init() {
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
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int) screen.getWidth(),
                              (int) screen.getHeight(), SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        log->error(SDL_GetError());
        SDL_Quit();
        return Pancake::Codes::ERROR;
    }
    afterWindowCreated();

//    beforeRendererCreated();
//    log->info("Create renderer");
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (renderer == nullptr) {
//        log->error(SDL_GetError());
//        Pancake::cleanup(window);
//        SDL_Quit();
//        return Pancake::Codes::ERROR;
//    }
//    afterRendererCreated();

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

    // Set opengl settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    log->info("Initialize imgui");
    ImGui_ImplSdlGL3_Init(window);

    log->info("Create painter");
    painter = Pancake::Graphics::Painter(camera, screen);
    painter.initialize();

    log->info("Load assets");
    loadAssets();

    log->info("Register default keyboard actions");
    keyboard.registerKeyPress(SDL_SCANCODE_ESCAPE, std::bind(&Pancake::Game::BaseGame::quitGame, this));
    keyboard.registerKeyPress(SDL_SCANCODE_F8, [this] {
        this->setFullscreen(Pancake::Game::BaseGame::WindowMode::WINDOWED);
    });
    keyboard.registerKeyPress(SDL_SCANCODE_F9, [this] {
        this->setFullscreen(Pancake::Game::BaseGame::WindowMode::FULLSCREEN_WINDOWED);
    });
    keyboard.registerKeyPress(SDL_SCANCODE_F10, [this] {
        this->debug = !this->debug;
    });

    log->info("Game initialized");
    initialized();

    return Pancake::Codes::OK;
}

void Pancake::Game::BaseGame::destroy() {
    Pancake::LogHandle log = Pancake::Log::getInstance("GAME");

    log->info("Shutdown imgui");
    ImGui_ImplSdlGL3_Shutdown();

    beforeDestroy();

    log->info("Destroy assets");
    destroyAssets();

    log->info("Delete asset manager");
    assets.cleanup();

    log->info("Delete painter");
    painter.cleanup();

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

Pancake::Game::BaseGame::BaseGame(std::string title, int width, int height) {
    setResolution(width, height);
    setTitle(title);
    camera.setPosition({0, 0});
    camera.setSize({width, height});
}

void Pancake::Game::BaseGame::run() {
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
        if (debug) {
            ImGui_ImplSdlGL3_NewFrame(window);

            debugUI(delta);

            updateUI(delta);
        }
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

void Pancake::Game::BaseGame::quitGame() {
    quit = true;
}

void Pancake::Game::BaseGame::setTitle(std::string title) {
    this->title = title;
    SDL_SetWindowTitle(this->window, title.c_str());
}

void Pancake::Game::BaseGame::setResolution(int width, int height) {
    this->screen = Pancake::Math::Rect(0, 0, width, height);
    SDL_SetWindowSize(this->window, width, height);
}

void Pancake::Game::BaseGame::setFullscreen(WindowMode mode) {
    this->windowMode = mode;
    SDL_SetWindowFullscreen(this->window, mode);

    int w, h;
    SDL_GetWindowSize(this->window, &w, &h);
    setResolution(w, h);
}

void Pancake::Game::BaseGame::toggleDebug() {
    debug = !debug;
}

void Pancake::Game::BaseGame::setDebug(bool debug) {
    this->debug = debug;
}

void Pancake::Game::BaseGame::debugUI(float delta) {
    ImGui::Begin("GAME");

    ImGui::LabelText("FPS", "%.2f", 1.0f / delta);
    ImGui::LabelText("Window", "w:%.f h:%.f", screen.getWidth(), screen.getHeight());
    ImGui::Spacing();
    ImGui::LabelText("Camera", "%.2f %.2f %.f %.f",
                     camera.getX(), camera.getY(),
                     camera.getWidth(), camera.getHeight());
    ImGui::Spacing();
    ImGui::LabelText("Assets", "%i", (int)assets.count());

    ImGui::End();
    ImGui::ShowTestWindow();
}
