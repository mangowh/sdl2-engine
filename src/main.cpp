#define SDL_MAIN_HANDLED // see SDL_MainReady documentation

#define SOL_ALL_SAFETIES_ON 1

#include "Engine.h"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include <sol/sol.hpp>
#include <yaml-cpp/yaml.h>

int main(int argc, char* argv[])
{
	SDL_SetMainReady();

	// load configuration
	Config config;
	try
	{
		YAML::Node node = YAML::LoadFile("config/config.yaml");

		if (node["playerSpeed"])
		{
			config.playerSpeed = node["playerSpeed"].as<int>();
		}
	}
	catch (const YAML::Exception& e)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << "\n" << "Error parsing YAML configuration" << std::endl;
		std::cerr << e.what() << std::endl;
	}

	// load lua scripts
	sol::state lua;
	lua.open_libraries(sol::lib::base);
	try
	{
		lua.script_file("scripts/script.lua");

		std::cout << "Lua script correctly loaded" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << "\n" << "Error loading Lua scripts" << std::endl;
		std::cerr << e.what() << std::endl;
	}

	Engine engine{ config };
	engine.run();

	return EXIT_SUCCESS;
}