#pragma once

#include "../Camera.h"
#include "../EntityManager.h"
#include "../Action.h"

class Scene {
public:
  virtual void init() = 0;
  virtual void update() = 0;

protected:
  Camera camera;
  EntityManager entityManager;

  // std::map<Action &, std::string> actionMap;

  // virtual void doActions() = 0;
};
