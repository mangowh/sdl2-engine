#pragma once

#include "Entity.h"
#include "Scene.h"
#include "Window.h"

extern Window gWindow;

class MegamarioScene : public Scene {
public:
  MegamarioScene() = default;

  void init() override;
  void update() override;

private:
  std::shared_ptr<Entity> player;
  std::shared_ptr<Entity> tilemap;

  void sUserInput();
  void sRender();
};
