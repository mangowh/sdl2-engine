#define SDL_MAIN_HANDLED // see SDL_MainReady documentation

#define SOL_ALL_SAFETIES_ON 1

#include "Engine.h"

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>
#include <sol/sol.hpp>
#include <yaml-cpp/yaml.h>

static void printException(std::exception e, std::string msg = "Error") {
  PLOG_ERROR << __FILE__ << ":" << __LINE__ << "\n" << msg;
  PLOG_ERROR << e.what();
}

int main(int, char *) {
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::verbose, &consoleAppender);

  SDL_SetMainReady();

  // load configuration
  Config config;
  try {
    YAML::Node node = YAML::LoadFile("config/config.yaml");

    if (node["playerSpeed"]) {
      config.playerSpeed = node["playerSpeed"].as<int>();
    }
  } catch (const YAML::Exception &e) {
    printException(e, "Error loading YAML configuration");

    return EXIT_FAILURE;
  }

  // load lua scripts
  sol::state lua;
  lua.open_libraries(sol::lib::base);

  try {
    lua.script_file("scripts/script.lua");
  } catch (const std::exception &e) {
    printException(e, "Error loading lua script");

    return EXIT_FAILURE;
  }

  Engine engine(config);
  engine.run();

  return EXIT_SUCCESS;
}
