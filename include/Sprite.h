#pragma once

#include "Texture.h"

class Sprite {
public:
  Sprite(SDL_Rect rect, Texture &texture) : rect(rect), texture(texture) {}

private:
  SDL_Rect rect;
  Texture &texture;
};
