#pragma once

#include "../Window.h"
#include "Scene.h"

extern Window window;

class MegamarioScene : public Scene {
public:
  MegamarioScene() = default;

  void init() override;
  void update() override;

private:
};
