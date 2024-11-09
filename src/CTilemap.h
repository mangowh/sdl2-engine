#pragma once

#include "./sdl/Texture.h"
#include "CCollision.h"
#include "Physics.h"

#include <string>
#include <utility>
#include <vector>

struct CTilemap {
  CTilemap(int size = 60) : size(size) {};

  int size;

  std::vector<std::pair<Physics::Vector2, Texture>> tiles;

  std::vector<std::pair<Physics::Vector2, CCollision>> collision;
};
