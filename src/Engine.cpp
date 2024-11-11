#include "Engine.h"

ActionManager actionManager;
Window window;
SceneManager sceneManager;

Engine::Engine(Config) {
  sceneManager.sceneMap.push_back(std::make_shared<MenuScene>()); // 0

  sceneManager.sceneMap.push_back(std::make_shared<GeometryWarsScene>()); // 1
  sceneManager.sceneMap.push_back(std::make_shared<MegamarioScene>()); // 2
  //sceneManager.sceneMap.push_back(std::make_shared<S>()) ; // 3

  sceneManager.setCurrentScene(0);

  window.addCallback([&]() {
    sUserInput();

    sceneManager.getCurrentScene()->update();

    currentFrame++;
  });

  actionManager.registerSubscriber(ActionName::togglePause, [&](Action) {
    if (!paused) {
      pause();
    } else {
      run();
    }
  });
}

void Engine::run() const {
  while (!window.shouldQuit) {
    if (!paused) {
      window.mainLoop();
    }
  }
}

void Engine::resume() { paused = false; }

void Engine::pause() { paused = true; }

void Engine::sUserInput() const {
  auto keyboardState = window.keyboardState;

  // Fullscreen
  // TODO use SDL_Event pool for
  if (keyboardState[SDL_SCANCODE_F]) {
    window.setFullscreen();
  }
}
