#include <list>
#include <iostream>

#define CLASS(name) class name {  \
public:                           \
private:                          \
};
#define COPY(name) name(const name&);
#define ASSIGN(name) name& operator=(const name&);

class Bindable {
public:
  virtual void bind() const = 0;
  
  virtual void unbind() const = 0;
};

/**
 *
 */
class Initializeable {
protected:
  bool initialized = false, released = false;

public:
  virtual void initialize() = 0;
  
  virtual void release() = 0;
};

/**
 *
 */
class Painter;

/**
 *
 */
class Updateable {
public:
  virtual void update(const float& delta) = 0;
};

/**
 *
 */
class Renderable {
public:
  virtual void render(const Painter& painter) = 0;
};

/**
 * Wraps glTexture
 */
class Texture : public Bindable, Initializeable {
private:
  int id = 0;
public:
  Texture(){};
  Texture(int id): id(id){};
  
  void bind() const override {
  }
  
  void unbind() const override {
  }
  
  void initialize() override {
  }
  
  void release() override {
  }
};

/**
 * Contains a Texture which can be rendered to the screen
 */
class Sprite : public Renderable {
private:
  const Texture& texture;

public:
  Sprite(const Texture& texture) : texture(texture) {}
  
  void render(const Painter& painter) override {
    texture.bind();
    texture.unbind();
  }
};

/**
 *
 */
class Polygon : public Renderable {
public:
  void render(const Painter& painter) override {}
};

/**
 *
 */
class Quad : public Polygon {
public:
  void render(const Painter& painter) override {}
};

/**
 *
 */
class Line : public Polygon {
public:
  void render(const Painter& painter) override {}
};

/**
 *
 */
class Triangle : public Polygon {
public:
  void render(const Painter& painter) override {}
};

/**
 * Some super cool painter
 */
class Painter : public Initializeable {
private:
  COPY(Painter)
  
  ASSIGN(Painter)

public:
  Painter() {}
  
  ~Painter() {
    if (!released) { std::cout << "Painter is not released" << '\n'; }
  }
  
  void initialize() {
    if (released) { return; }
    initialized = true;
  }
  
  void release() {
    if (!initialized) { return; }
    released = true;
  }
  
  void render(const Renderable& renderable) {}
};

class Interface;

/**
 *
 */
class Widget : public Renderable, Updateable {
protected:
  const Interface* interface;

public:
  void setInterface(const Interface* interface) {
    this->interface = interface;
  }
  
  virtual ~Widget() {}
};

/**
 *
 */
typedef Widget* WidgetHandle;
/**
 *
 */
typedef std::list<WidgetHandle> Widgets;

/**
 *
 */
class Interface : public Renderable, Updateable, Initializeable {
private:
  Widgets widgets;
  
  COPY(Interface)
  
  ASSIGN(Interface)

public:
  Interface() {}
  
  ~Interface() {
    if (!released) { std::cout << "Interface is not released" << '\n'; }
  }
  
  void initialize() override {
    if (released) { return; }
    initialized = true;
  }
  
  void release() override {
    if (!initialized) { return; }
    
    for (auto& widget: widgets) {
      delete widget;
      widget = nullptr;
    }
    
    released = true;
  }

public:
  
  WidgetHandle add(WidgetHandle handle) {
    handle->setInterface(this);
    return nullptr;
  };
  
  void render(const Painter& painter) override {}
  
  void update(const float& delta) override {}
};

/**
 *
 */
class Button : public Widget {
public:
  void render(const Painter& painter) override {}
  
  void update(const float& delta) override {}
};

/**
 *
 */
class Label : public Widget {
public:
  void render(const Painter& painter) override {}
  
  void update(const float& delta) override {}
};

/**
 *
 */
class Game : public Renderable, Updateable, Initializeable {
private:
  Interface interface;
  
  Painter painter;
  
  ASSIGN(Game)
  
  COPY(Game)

public:
  Game() {}
  
  ~Game() {
    if (!released) { std::cout << "Game is not released" << '\n'; }
  }
  
  void initialize() override {
    painter.initialize();
    interface.initialize();
    interface.add(new Button());
  }
  
  void release() override {
    painter.release();
    interface.release();
  }
  
  void run() {
    update(0);
    render(painter);
  }
};

/**
 *
 */
class MyGame : public Game {
public:
  void render(const Painter& painter) override {
  }

private:
  void update(const float& delta) override {
  }
};

/**
 *
 */
int main() {
  MyGame game;
  game.initialize();
  game.run();
  game.release();
  return 0;
}