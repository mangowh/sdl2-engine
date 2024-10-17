#define SDL_MAIN_HANDLED // see SDL_MainReady documentation

#include "Engine.h"

int main(int argc, char* argv[])
{
	SDL_SetMainReady();

	Engine engine;
	engine.run();

	return EXIT_SUCCESS;
}