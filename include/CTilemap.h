#pragma once

#include "CCollision.h"
#include "Physics.h"
#include "Texture.h"

#include <utility>
#include <vector>

struct CTilemap {
  CTilemap(int size = 60) : size(size) {};

  int size;

  std::vector<std::pair<Physics::Vector2, Texture>> tiles;

  std::vector<std::pair<Physics::Vector2, CCollision>> collision;
};
