#pragma once

#include "Text.h"

#include <memory>
#include <string>

struct CText {
  std::string text{};
  SDL_Color color{255, 255, 255};

  std::shared_ptr<Text> textObj;

  CText(std::string text) : text(text) {};
  CText(std::string text, SDL_Color color) : text(text), color(color) {};
};
