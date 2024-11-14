#pragma once

#include "Action.h"

#include <functional>
#include <map>
#include <vector>

typedef std::function<void(Action)> ActionCallback;

class ActionManager {
public:
  ActionManager();

  void registerSubscriber(ActionName actionName, ActionCallback actionCallback);
  void dispatchAction(ActionName actionName, ActionType actionType);

private:
  std::map<ActionName, std::vector<ActionCallback>> subscribers{};
};
