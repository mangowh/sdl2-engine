#define SDL_MAIN_HANDLED // see SDL_MainReady documentation

#define SOL_ALL_SAFETIES_ON 1

#include "Engine.h"

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include <sol/sol.hpp>
#include <yaml-cpp/yaml.h>

static void printException(std::runtime_error e) {
  std::cerr << __FILE__ << ":" << __LINE__ << "\n" << "Error" << std::endl;
  std::cerr << e.what() << std::endl;
}

int main(int, char *) {
  SDL_SetMainReady();

  // load configuration
  Config config;
  try {
    YAML::Node node = YAML::LoadFile("config/config.yaml");

    if (node["playerSpeed"]) {
      config.playerSpeed = node["playerSpeed"].as<int>();
    }
  } catch (const YAML::Exception &e) {
    printException(e);

    return EXIT_FAILURE;
  }

  // load lua scripts
  sol::state lua;
  lua.open_libraries(sol::lib::base);

  try {
    lua.script_file("scripts/script.lua");
  } catch (const std::exception &e) {
    std::cerr << __FILE__ << ":" << __LINE__ << "\n"
              << "Error loading Lua scripts" << std::endl;
    std::cerr << e.what() << std::endl;

    return EXIT_FAILURE;
  }

  Engine engine(config);
  engine.run();

  return EXIT_SUCCESS;
}
