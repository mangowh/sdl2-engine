#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Texture {
  SDL_Renderer *renderer;
  SDL_Texture *texture;

public:
  Texture(SDL_Renderer *renderer, std::string path);
};
