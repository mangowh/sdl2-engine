#pragma once

#include "Texture.h"

class Sprite {
  SDL_Rect rect;
  Texture &texture;

public:
  Sprite(SDL_Rect rect, Texture &texture) : rect(rect), texture(texture) {}
};
