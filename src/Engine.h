#pragma once

#include "ActionManager.h"
#include "EntityManager.h"
#include "Random.h"
#include "Scenes/GeometryWarsScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/Scene.h"
#include "Window.h"

struct Config {
  int initialScene{0};
  float playerSpeed{10.0f};
};

class Engine {
public:
  Engine(Config config = {});

  void run();
  void resume();
  void pause();

  auto isRunning() const { return paused; }

  Window window = Window(actionManager);

private:
  Config config;
  ActionManager actionManager;

  int currentFrame = 0;
  bool paused = false;

  std::shared_ptr<Scene> currentScene;

  void sUserInput();
};
