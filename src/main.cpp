#define SDL_MAIN_HANDLED // see SDL_MainReady documentation

#define SOL_ALL_SAFETIES_ON 1

#include "Engine.h"

#include <iostream>

#include <sol/sol.hpp>

int main(int argc, char* argv[])
{
	SDL_SetMainReady();

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script_file("lua/script.lua");

	Engine engine;
	engine.run();

	return EXIT_SUCCESS;
}