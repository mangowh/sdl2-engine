#pragma once

#include <iostream>

enum class ActionName { left, top, right, bottom };
enum class ActionType { start, end };

class Action {
  ActionName name;
  ActionType type;

public:
  //Action(const ActionName &name, const ActionType &type)
  //    : name(name), type(type) {};

  //const ActionName &name() const { return name; };
  //const ActionType &type() const { return type; };
};
