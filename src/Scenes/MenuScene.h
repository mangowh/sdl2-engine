#pragma once

#include "../Window.h"
#include "Scene.h"

class MenuScene : public Scene {
public:
  MenuScene(Window &window);

  void init() override;
  void update() override;

  void sRender();

private:
  Window &window;
};
