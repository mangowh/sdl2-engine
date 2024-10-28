#include "Engine.h"

Engine::Engine(Config config) {
  currentScene = std::make_shared<GeometryWarsScene>(window);

  currentScene->init();

  window.addCallback([this]() {
    sUserInput();

    currentScene->update();

    currentFrame++;
  });

  while (!window.shouldQuit) {
    window.mainLoop();
  }
}

void Engine::run() { paused = false; }

void Engine::pause() { paused = true; }

void Engine::sUserInput() {
  // TODO remove SDL references in Engine

  auto keyboardState = window.keyboardState;

  // Pause
  // TODO use SDL_Event pool for
  if (keyboardState[SDL_SCANCODE_P]) {
    if (!paused) {
      pause();
    } else {
      run();
    }
  }

  // Fullscreen
  // TODO use SDL_Event pool for
  if (keyboardState[SDL_SCANCODE_F]) {
    window.setFullscreen();
  }
}
