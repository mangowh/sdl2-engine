#pragma once

#include "../CTilemap.h"
#include "../Entity.h"
#include "../Window.h"
#include "Scene.h"

#include <sol/sol.hpp>

extern Window window;

class MegamarioScene : public Scene {
public:
  MegamarioScene() = default;

  void init() override;
  void update() override;

private:
  std::shared_ptr<Entity> player;
  std::shared_ptr<Entity> tilemap;

  void sRender();
};
