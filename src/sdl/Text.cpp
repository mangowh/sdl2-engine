#include "Text.h"

Text::Text(SDL_Renderer *renderer, std::string text, SDL_Color color)
    : renderer(renderer) {
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(defaultFont, text.c_str(), color);

  if (textSurface == NULL) {
    printf("Could not create surface message! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  texture = SDL_CreateTextureFromSurface(renderer, textSurface);

  dstRect = {0, 0, textSurface->w, textSurface->h};
}

void Text::setColor(SDL_Color &color) {
  auto res = SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

  if (res == -1) {
    printf("Could not set color! SDL_Error: %s\n", SDL_GetError());
    return;
  }
}

// Text::~Text() {
//   SDL_DestroyTexture(texture);
//   TTF_CloseFont(defaultFont);
// }

void Text::draw() { draw(0, 0); }

void Text::draw(int x = 0, int y = 0) {
  dstRect.x = x;
  dstRect.y = y;

  SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}
