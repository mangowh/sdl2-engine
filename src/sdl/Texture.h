#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

struct Texture {
  Texture(SDL_Renderer *renderer, std::string path)
      : renderer(renderer), texture(IMG_LoadTexture(renderer, path.c_str())) {};

  const SDL_Renderer *renderer;
  const SDL_Texture *texture;
};
