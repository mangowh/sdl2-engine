#pragma once

#include "./sdl/Texture.h"
#include "Vector2.h"

#include <string>
#include <utility>
#include <vector>

struct CTilemap {
  CTilemap(int size = 60) : size(size) {};

  int size;

  std::vector<std::pair<Vector2, Texture>> tiles;

  std::vector<std::pair<Vector2, Texture>> debugTiles;
};
