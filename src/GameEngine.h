#pragma once

#include "./Scenes/Scene.h"
#include "Assets.h"
#include "Window.h"

#include <map>
#include <string>

class GameEngine {
  Window window;

  std::string currentScene;
  std::map<std::string, Scene> scenes;
  Assets assets;
  bool running;

public:
  void init();
  Scene currentScene();
  void run();
  void update();
  void quit();
  void changeScene(std::string, Scene);
  Assets &assets() { return assets; }
  Window &window() { return window; }

  void sUserInput();
};
