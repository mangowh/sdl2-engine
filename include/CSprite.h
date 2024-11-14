#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

struct CSprite {
  CSprite(SDL_Renderer *renderer) : renderer(renderer) {
    texture = IMG_LoadTexture(renderer, path.c_str());
  }

  std::string path{"./assets/c.png"}; // TODO

  int width{60};
  int height{60};

  SDL_Texture *getTexture() { return texture; };

private:
  SDL_Renderer *renderer;
  SDL_Texture *texture;
};
