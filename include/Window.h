#pragma once

#include "ActionManager.h"
#include "CShape.h"
#include "CTransform.h"
#include "Entity.h"
#include "Text.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#include <memory>
#include <string>
#include <vector>

extern ActionManager gActionManager;

class Window {
public:
  Window();
  ~Window();

  void mainLoop();
  bool shouldQuit = false;

  const Uint8 *keyboardState;

  void addCallback(std::function<void(void)> func);
  void clear() const;
  void close();

  void render() const;

  int getWidth() const;
  int getHeight() const;

  void setFullscreen() const;

  SDL_Renderer *getRenderer() const { return renderer; };

  // callbacks
  std::function<void(Physics::Vector2)> onClick = NULL;
  std::function<void(Physics::Vector2)> onRightClick = NULL;

  // drawing
  void drawShape(std::shared_ptr<CTransform> transform,
                 std::shared_ptr<CShape> shape) const;
  void drawPoint(int x, int y, SDL_Color color) const;
  void drawRect(int x, int y, int width, int height, SDL_Color color,
                bool fill = true) const;
  void drawTriangle(Physics::Vector2 v1, Physics::Vector2 v2,
                    Physics::Vector2 v3, SDL_Color color) const;
  void drawCircle(Physics::Vector2 center, int radius, SDL_Color color,
                  int numSegments) const;

  void drawText(Text text) const;

  void drawDebug(std::shared_ptr<Entity> e) const;

  // experimental
  void initGL();
  void renderGL() const;

private:
  /* Window title */
  const std::string windowTitle = "test";
  /* Screen width */
  const int screenWidth = 1920;
  /* Screen height */
  const int screenHeight = 1080;
  /* The window object to render to */
  SDL_Window *sdlWindow = NULL;
  /* The surface contained by the window */
  SDL_Surface *surface = NULL;
  SDL_Renderer *renderer = NULL;

  TTF_Font *font = NULL;
  TTF_Font *gFont = NULL;

  std::vector<std::function<void()>> frameCallbacks = {};

  /* Event handler */
  void handleEvents();
};
