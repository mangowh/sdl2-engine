#pragma once

#include "ActionManager.h"
#include "EntityManager.h"
#include "Random.h"
#include "SceneManager.h"
#include "Scenes/GeometryWarsScene.h"
#include "Scenes/MegamarioScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/Scene.h"
#include "Window.h"

#include <memory>

extern ActionManager actionManager;
extern Window window;
extern SceneManager sceneManager;

struct Config {
  int initialScene{0};
  float playerSpeed{10.0f};
};

class Engine {
public:
  Engine(Config config = {});

  void run() const;
  void resume();
  void pause();

  auto isRunning() const { return paused; }

private:
  Config config;

  int currentFrame = 0;
  bool paused = false;

  void sUserInput() const;
};
