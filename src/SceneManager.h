#pragma once

// #include "Scenes/GeometryWarsScene.h"
// #include "Scenes/MenuScene.h"
#include "Scenes/Scene.h"

#include <memory>
#include <vector>

class SceneManager {
public:
  SceneManager();

  std::shared_ptr<Scene> getCurrentScene();
  void setCurrentScene(int sceneId);

  // private:
  std::shared_ptr<Scene> currentScene;
  std::vector<std::shared_ptr<Scene>> sceneMap{};
};
