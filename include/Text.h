#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

class Text {
public:
  Text(SDL_Renderer *renderer, std::string text,
       SDL_Color color = {255, 255, 255});
  ~Text();

  void setColor(SDL_Color &color);

  void draw();
  void draw(int x, int y);

private:
  TTF_Font *defaultFont = TTF_OpenFont("assets/fonts/NotoSans-Regular.ttf", 24);

  SDL_Renderer *renderer = nullptr;
  SDL_Surface *textSurface = nullptr;
  SDL_Texture *texture = nullptr;
  SDL_Rect dstRect{};
};
