#pragma once

#include "Physics.h"

#include <vector>

struct CTransform {
  Physics::Vector2 position{0, 0};
  Physics::Vector2 previousPosition{0, 0};

  Physics::Vector2 localPosition{0, 0};

  Physics::Vector2 origin{0, 0};

  Physics::Vector2 scale{1, 1};
  Physics::Vector2 velocity{0, 0};

  float angle = 0;

  CTransform() {};
  CTransform(const Physics::Vector2 &p) : position(p) {}
  CTransform(const Physics::Vector2 &p, const Physics::Vector2 &v)
      : position(p), velocity(v) {}
};
