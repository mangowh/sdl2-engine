#pragma once

#include "./sdl/Text.h"

#include <string>

struct CText {
  std::string text{};
  SDL_Color color{255, 255, 255};

  std::shared_ptr<Text> textObj;

  CText(std::string text) : text(text) {};
  CText(std::string text, SDL_Color color) : text(text), color(color) {};
};
