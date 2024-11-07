#pragma once

#include "../ActionManager.h"
#include "../CText.h"
#include "../SceneManager.h"
#include "../Window.h"
#include "Scene.h"

#include <vector>

extern ActionManager actionManager;
extern Window window;
extern SceneManager sceneManager;

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
