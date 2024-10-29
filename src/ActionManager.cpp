#include "ActionManager.h"

ActionManager::ActionManager() {}

void ActionManager::registerSubscriber(ActionName actionName,
                                       ActionCallback actionCallback) {
  subscribers[actionName].push_back(actionCallback);
}

void ActionManager::dispatchAction(ActionName actionName,
                                   ActionType actionType) {
  const auto &actionSubs = subscribers[actionName];

  for (const auto &sub : actionSubs) {
    sub(Action(actionName, actionType));
  }
}
