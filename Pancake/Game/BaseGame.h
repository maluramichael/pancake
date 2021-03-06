#ifndef PANCAKE_BASEGAME
#define PANCAKE_BASEGAME

#include <GL/glew.h>

#include "Assets.h"
#include "Keyboard.h"
#include "Timer.h"
#include "Camera.h"
#include "Constants.h"
#include "Log.h"
#include "Cleanup.h"

#include "../UI/imgui.h"
#include "../UI/imgui_impl_sdl_gl3.h"

/**
 * Creates game loop with update and render posibilities
 */
class BaseGame {
public:
  enum WindowMode {
    WINDOWED = 0,
    FULLSCREEN = SDL_WINDOW_FULLSCREEN,
    FULLSCREEN_WINDOWED = SDL_WINDOW_FULLSCREEN_DESKTOP
  };
  
  BaseGame(std::string title = "Game", int width = 640, int height = 480);
  
  void run();
  
  void quitGame();
  
  void setTitle(std::string title);
  
  void setResolution(int width, int height);
  
  void setFullscreen(WindowMode mode);

protected:
  Camera camera;
  
  Rect screen;
  
  Painter painter;
  
  Assets assets;
  
  Keyboard keyboard;
  
  SDL_Window* window = nullptr;
  
  SDL_Renderer* renderer = nullptr;
  
  SDL_GLContext glContext = nullptr;
  
  void toggleDebug();
  
  void setDebug(bool debug);

private:
  bool quit = false;
  
  bool debug = false;
  
  std::string title = "";
  
  WindowMode windowMode = WINDOWED;
  
  int init();
  
  void destroy();
  
  void debugUI(float delta);
  
  virtual void beforeSDLInitialized() {}
  
  virtual void afterSDLInitialized() {}
  
  virtual void beforeWindowCreated() {}
  
  virtual void afterWindowCreated() {}
  
  virtual void beforeRendererCreated() {}
  
  virtual void afterRendererCreated() {}
  
  virtual void beforeOpenGLContextCreated() {}
  
  virtual void afterOpenGLContextCreated() {}
  
  virtual void beforeGLEWInit() {}
  
  virtual void afterGLEWInit() {}
  
  virtual void loadAssets() {}
  
  virtual void initialized() {}
  
  virtual void beforeDestroy() {}
  
  virtual void destroyAssets() {}
  
  virtual void destroyed() {}
  
  virtual void update(float delta) {}
  
  virtual void updateUI(float delta) {}
  
  virtual void render() {}
  
  virtual void renderUI() {}
  
  virtual void processEvent(SDL_Event* event) {};
};

#endif
