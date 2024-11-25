#pragma once

#include "ActionManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"

extern ActionManager gActionManager;
extern Window gWindow;
extern SceneManager gSceneManager;

class MenuScene : public Scene {
public:
  MenuScene();
  ~MenuScene();

  void init() override;
  void update() override;

  void sRender();

private:
  EntityVec options;
  int currentSelectedOption{0};
};
