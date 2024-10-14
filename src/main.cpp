#include "window.h"

#define SDL_MAIN_HANDLED // see SDL_MainReady documentation at line 9
#include <SDL2/SDL.h>

void function1(SDL_Renderer* renderer) {
    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Render rect
    SDL_RenderFillRect(renderer, &r);
}

int main(int argc, char* argv[])
{
	SDL_SetMainReady();

	Window window = Window();

	window.addRenderCallback(function1);

	window.open();

	return EXIT_SUCCESS;
}