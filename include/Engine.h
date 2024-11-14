#pragma once

#include "ActionManager.h"
#include "SceneManager.h"
#include "Window.h"

extern ActionManager actionManager;
extern Window window;
extern SceneManager sceneManager;

struct Config {
  int initialScene{0};
  int playerSpeed{10};
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
