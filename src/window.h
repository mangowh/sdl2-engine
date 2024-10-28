#pragma once

#include "CShape.h"
#include "CTransform.h"
#include "Entity.h"
#include "sdl/Texture.h"

#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

class Window {

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
  /* Event handler */
  SDL_Event pollEvent();
  std::vector<std::function<void(void)>> frameCallbacks = {};

  std::vector<std::function<void(void)>> &getC() { return frameCallbacks; }

public:
  Window();
  ~Window();

  void mainLoop();
  bool shouldQuit = false;

  const Uint8 *keyboardState;

  void addCallback(std::function<void(void)> func);
  void clear() const;
  void close();

  Texture loadImage(std::string path);

  void render() const;

  int getWidth() const;
  int getHeight() const;

  void setFullscreen() const;

  // callbacks
  std::function<void(Vector2)> onClick = NULL;
  std::function<void(Vector2)> onRightClick = NULL;

  // drawing
  void drawShape(std::shared_ptr<CTransform> transform,
                 std::shared_ptr<CShape> shape) const;
  void drawPoint(int x, int y, SDL_Color color) const;
  void drawRect(int x, int y, int width, int height, SDL_Color color,
                bool fill = true) const;
  void drawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, SDL_Color color) const;
  void drawCircle(Vector2 center, float radius, SDL_Color color,
                  int numSegments) const;

  void drawDebug(std::shared_ptr<Entity> e) const;

  // experimental
  void initGL();
  void renderGL() const;
};
