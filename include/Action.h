#pragma once

enum class ActionName { esc, left, top, right, bottom, confirm, togglePause };
enum class ActionType { start, end };

class Action {
public:
  Action(const ActionName &name, const ActionType &type)
      : name(name), type(type) {};

  const ActionName name;
  const ActionType type;

  const ActionName &getName() const { return name; };
  const ActionType &getType() const { return type; };
};
