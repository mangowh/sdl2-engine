#include "Texture.h"

Texture::Texture(SDL_Renderer *renderer, std::string path) {
  this->renderer = renderer;
  texture =
      IMG_LoadTexture(renderer, path.c_str()); // Replace with your image path

  if (texture == nullptr) {
    std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
  }
}
