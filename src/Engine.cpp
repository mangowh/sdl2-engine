#include "Engine.h"

#include "GeometryWarsScene.h"
#include "MegamarioScene.h"
#include "MenuScene.h"

// TODO inline/const
ActionManager gActionManager;
Window gWindow;
SceneManager gSceneManager;

Engine::Engine(Config) {
  gSceneManager.sceneMap.push_back(std::make_shared<MenuScene>()); // 0

  gSceneManager.sceneMap.push_back(std::make_shared<GeometryWarsScene>()); // 1
  gSceneManager.sceneMap.push_back(std::make_shared<MegamarioScene>());    // 2
  // sceneManager.sceneMap.push_back(std::make_shared<S>()) ; // 3

  gSceneManager.setCurrentScene(0);

  gWindow.addCallback([&]() {
    sUserInput();

    gSceneManager.getCurrentScene()->update();

    currentFrame++;
  });

  gActionManager.registerSubscriber(ActionName::togglePause, [&](Action) {
    if (!paused) {
      pause();
    } else {
      run();
    }
  });
}

void Engine::run() const {
  while (!gWindow.shouldQuit) {
    if (!paused) {
      gWindow.mainLoop();
    }
  }
}

void Engine::resume() { paused = false; }

void Engine::pause() { paused = true; }

void Engine::sUserInput() const {
  auto keyboardState = gWindow.keyboardState;

  // Fullscreen
  // TODO use SDL_Event pool for
  if (keyboardState[SDL_SCANCODE_F]) {
    gWindow.setFullscreen();
  }
}
