#include "Engine.h"

Engine::Engine(Config config) {
  currentScene = std::make_shared<MenuScene>(window);

  currentScene->init();

  window.addCallback([this]() {
    sUserInput();

    currentScene->update();

    currentFrame++;
  });

  actionManager.registerSubscriber(ActionName::confirm, [&](Action action) {
    currentScene = std::make_shared<GeometryWarsScene>(window);
  });

  actionManager.registerSubscriber(ActionName::togglePause, [&](Action action) {
    if (!paused) {
      pause();
    } else {
      run();
    }
  });
}

void Engine::run() {
  while (!window.shouldQuit) {
    if (!paused) {
      window.mainLoop();
    }
  }
}

void Engine::resume() { paused = false; }

void Engine::pause() { paused = true; }

void Engine::sUserInput() {
  auto keyboardState = window.keyboardState;

  // Fullscreen
  // TODO use SDL_Event pool for
  if (keyboardState[SDL_SCANCODE_F]) {
    window.setFullscreen();
  }
}
