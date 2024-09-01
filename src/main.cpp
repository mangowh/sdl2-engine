#include "window.h"

// see SDL_MainReady at line 9
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
	SDL_SetMainReady();

	Window window = Window();

	// Main loop
	while (!window.mainLoop()) {}

	return 0;
}