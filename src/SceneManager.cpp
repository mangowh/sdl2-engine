#include "SceneManager.h"

SceneManager::SceneManager() {}

std::shared_ptr<Scene> SceneManager::getCurrentScene() { return currentScene; }

void SceneManager::setCurrentScene(int sceneId) {
  currentScene = sceneMap[sceneId];
  currentScene->init();
}
