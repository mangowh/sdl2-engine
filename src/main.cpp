#include "Engine.h"

#define SDL_MAIN_HANDLED // see SDL_MainReady documentation at line 9
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
	SDL_SetMainReady();

	Engine engine;

	return EXIT_SUCCESS;
}