#pragma once

#include <ctime>
#include <iostream>

enum class ActionName { left, top, right, bottom, confirm, togglePause };
enum class ActionType { start, end };

class Action {
  std::time_t time;

  ActionName name;
  ActionType type;

public:
  Action(const ActionName &name, const ActionType &type)
      : name(name), type(type) {};

  const ActionName &getName() const { return name; };
  // const ActionType &type() const { return type; };
};
