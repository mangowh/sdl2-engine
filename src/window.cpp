#include "Window.h"

#include "Action.h"

#include <cmath>
#include <functional>
#include <iostream>

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS; // Frame delay in milliseconds

Window::Window() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize: %s\n", SDL_GetError());
    return;
  }

  // Text redenering
  if (TTF_Init()) {
    printf("TTF_Init Error: %s\n", TTF_GetError());
    return;
  }

  font = TTF_OpenFont("assets/fonts/NotoSans-Regular.ttf", 24);
  if (font == NULL) {
    printf("Error loading font: %s\n", TTF_GetError());
    return;
  }

  // Initialize SDL_image
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
    return;
  }

  // Create window
  sdlWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, screenWidth,
                               screenHeight, SDL_WINDOW_SHOWN);

  if (sdlWindow == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  renderer = SDL_CreateRenderer(
      sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == NULL) {
    printf("Could not create renderer! SDL_Error: %s\n", SDL_GetError());
    return;
  }
}

Window::~Window() { close(); }

void Window::mainLoop() {
  Uint32 frameStart = SDL_GetTicks(); // Start time for frame

  handleEvents();

  // Get the keyboard state
  keyboardState = SDL_GetKeyboardState(nullptr);

  for (auto &func : frameCallbacks) {
    func();
  }

  // Calculate frame time and delay to maintain fixed FPS
  Uint32 frameTime = SDL_GetTicks() - frameStart;
  if (frameTime < FRAME_DELAY) {
    SDL_Delay(FRAME_DELAY -
              frameTime); // Delay the remaining time to maintain FPS
  }
}

void Window::addCallback(std::function<void(void)> func) {
  // TODO prevent adding while iterating
  frameCallbacks.push_back(func);
}

void Window::clear() const {
  SDL_SetRenderDrawColor(renderer, 0, 0, 25, 255);
  SDL_RenderClear(renderer);
}

void Window::close() {
  // Destroy window
  if (sdlWindow) {
    SDL_DestroyWindow(sdlWindow);
    sdlWindow = NULL;
  }

  IMG_Quit();
  TTF_Quit();

  // Quit SDL subsystems
  SDL_Quit();
}

void Window::handleEvents() {
  // Handle events on queue
  SDL_Event event;
  SDL_PollEvent(&event);

  // User requests quit
  if (event.type == SDL_QUIT) {
    shouldQuit = true;
  }

  if (onClick && event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_LEFT) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    Physics::Vector2 coords = Physics::Vector2(x, y);
    onClick(coords);
  }

  if (onRightClick && event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_RIGHT) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    Physics::Vector2 coords = Physics::Vector2(x, y);
    onRightClick(coords);
  }

  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case (SDLK_ESCAPE): {
      gActionManager.dispatchAction(ActionName::esc, ActionType::start);
      break;
    }

    case (SDLK_a): {
      gActionManager.dispatchAction(ActionName::left, ActionType::start);
      break;
    }

    case (SDLK_w): {
      gActionManager.dispatchAction(ActionName::top, ActionType::start);
      break;
    }

    case (SDLK_d): {
      gActionManager.dispatchAction(ActionName::right, ActionType::start);
      break;
    }

    case (SDLK_s): {
      gActionManager.dispatchAction(ActionName::bottom, ActionType::start);
      break;
    }

    case (SDLK_SPACE): {
      gActionManager.dispatchAction(ActionName::confirm, ActionType::start);
      break;
    }

    case (SDLK_p): {
      gActionManager.dispatchAction(ActionName::togglePause, ActionType::start);
      break;
    }
    }
  }
}

void Window::render() const { SDL_RenderPresent(renderer); }

int Window::getWidth() const {
  int w;

  SDL_GetRendererOutputSize(renderer, &w, NULL);

  return w;
}

int Window::getHeight() const {
  int h;

  SDL_GetRendererOutputSize(renderer, NULL, &h);

  return h;
}

void Window::setFullscreen() const {
  SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
}

void Window::drawShape(std::shared_ptr<CTransform> transform,
                       std::shared_ptr<CShape> shape) const {
  SDL_Color color = {.r = shape->color.r,
                     .g = shape->color.g,
                     .b = shape->color.b,
                     .a = shape->color.a};

  if (shape->type == triangle) {
    drawTriangle(shape->verts[0], shape->verts[1], shape->verts[2], color);
  } else {
    drawRect(transform->position.x, transform->position.y, shape->width,
             shape->height, color);
  }
}

void Window::drawPoint(int x, int y, SDL_Color color) const {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  SDL_RenderDrawPoint(renderer, x, y);
}

void Window::drawRect(int x, int y, int width, int height, SDL_Color color,
                      bool fill) const {
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = width;
  r.h = height;

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  if (fill) {
    SDL_RenderFillRect(renderer, &r);
  } else {
    SDL_RenderDrawRect(renderer, &r);
  }
}

void Window::drawTriangle(Physics::Vector2 v1, Physics::Vector2 v2,
                          Physics::Vector2 v3, SDL_Color color) const {
  const std::vector<SDL_Vertex> verts = {
      {SDL_FPoint{(float)v1.x, (float)v1.y}, color},
      {SDL_FPoint{(float)v2.x, (float)v2.y}, color},
      {SDL_FPoint{(float)v3.x, (float)v3.y}, color}};

  SDL_RenderGeometry(renderer, nullptr, verts.data(), (int)verts.size(),
                     nullptr, 0);
}

void Window::drawCircle(Physics::Vector2 center, int radius, SDL_Color color,
                        int numSegments = 100) const {
  std::vector<SDL_Vertex> vertices;

  // Create vertices around the perimeter of the circle
  for (int i = 0; i <= numSegments; ++i) {
    float theta =
        2.0f * (float)M_PI * float(i) / float(numSegments); // Angle in radians
    float x = (float)center.x + radius * cosf(theta);       // X coordinate
    float y = (float)center.y + radius * sinf(theta);       // Y coordinate

    SDL_Vertex vertex;
    vertex.position.x = x;
    vertex.position.y = y;
    vertex.color = color;
    vertices.push_back(vertex);
  }

  // Draw line segments by creating degenerate triangles
  // Each pair of consecutive vertices forms the line
  for (int i = 0; i < numSegments; ++i) {
    SDL_SetRenderDrawColor(renderer, vertices[i].color.r, vertices[i].color.g,
                           vertices[i].color.b, vertices[i].color.a);

    SDL_RenderDrawLine(
        renderer, (int)vertices[i].position.x, (int)vertices[i].position.y,
        (int)vertices[i + 1].position.x, (int)vertices[i + 1].position.y);
  }
}

void Window::drawDebug(std::shared_ptr<Entity> e) const {
  const SDL_Color transformDebugColor = {255, 30, 40};
  const SDL_Color collisionDebugColor = {15, 30, 240};
  const SDL_Color tilemapDebugColor = {200, 200, 205, 10};
  const SDL_Color spriteDebugColor = {1, 200, 30, 10};

  if (e->cTilemap) {
    const auto size = e->cTilemap->size;
    const auto width = getWidth();
    const auto height = getHeight();

    SDL_SetRenderDrawColor(renderer, tilemapDebugColor.r, tilemapDebugColor.g,
                           tilemapDebugColor.b, tilemapDebugColor.a);

    for (int i = 0; i < width; i += size) {
      SDL_RenderDrawLine(renderer, i, 0, i, height);
    }

    for (int i = 0; i < height; i += size) {
      SDL_RenderDrawLine(renderer, 0, i, width, i);
    }

    for (auto &colliderData : e->cTilemap->collision) {
      const auto c = std::make_shared<CCollision>(colliderData.second);

      const auto pos = c->center;
      drawRect(pos.x - 3, pos.y - 3, 6, 6, collisionDebugColor);

      if (c->shape == ColliderShape::circle) {
        drawCircle(pos, c->radius, collisionDebugColor);
      } else {
        drawRect(c->p1.x, c->p1.y, c->p2.x - c->p1.x, c->p2.y - c->p1.y,
                 collisionDebugColor, false);
      }
    }
  }

  if (e->cTransform) {
    const auto pos = e->cTransform->position;

    drawRect(pos.x - 3, pos.y - 3, 6, 6, transformDebugColor);

    drawRect(pos.x - 3, pos.y - 3, 6, 6, spriteDebugColor);

    // if (e->cSprite) {
    //   drawRect(e->cTransform->position.x, e->cTransform->position.y,
    //            e->cSprite->width, e->cSprite->height, spriteDebugColor,
    //            false);
    // }
  }

  if (e->cCollision) {
    const auto pos = e->cCollision->center;
    drawRect(pos.x - 3, pos.y - 3, 6, 6, collisionDebugColor);

    if (e->cCollision->shape == ColliderShape::circle) {
      drawCircle(pos, e->cCollision->radius, collisionDebugColor);
    } else {
      drawRect(e->cCollision->p1.x, e->cCollision->p1.y,
               e->cCollision->p2.x - e->cCollision->p1.x,
               e->cCollision->p2.y - e->cCollision->p1.y, collisionDebugColor,
               false);
    }
  }
}

// experimental
void Window::initGL() {
  GLenum error = GL_NO_ERROR;

  // Initialize Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Check for error
  error = glGetError();
  if (error != GL_NO_ERROR) {
    throw "Cannot initialize Projection Matrix";
  }

  // Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Check for error
  error = glGetError();
  if (error != GL_NO_ERROR) {
    throw "Cannot initialize Modelview Matrix";
  }

  // Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  // Check for error
  error = glGetError();
  if (error != GL_NO_ERROR) {
    throw "Cannot initialize clear color";
  }
}

void Window::renderGL() const {
  // EXAMPLE CUBE
  glClear(GL_COLOR_BUFFER_BIT);

  glRotatef(0.4f, 0.0f, 1.0f, 2.0f); // Rotate The cube around the Y axis
  glRotatef(0.2f, 1.0f, 1.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);

  glBegin(GL_QUADS);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, -0.5f);
  glVertex2f(0.5f, 0.5f);
  glVertex2f(-0.5f, 0.5f);
  glEnd();
  // ! END EXAMPLE CUBE

  SDL_GL_SwapWindow(sdlWindow);
}
