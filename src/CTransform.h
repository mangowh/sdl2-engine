#pragma once

#include "Vector2.h"

#include <vector>

struct CTransform {
  Vector2 position{0.0f, 0.0f};
  Vector2 previousPosition{0.0f, 0.0f};

  Vector2 localPosition{0.0f, 0.0f};

  Vector2 origin{0.0f, 0.0f};

  Vector2 scale{1.0, 1.0};
  Vector2 velocity{0, 0};

  float angle = 0;

  CTransform() {};
  CTransform(const Vector2 &p) : position(p) {}
  CTransform(const Vector2 &p, const Vector2 &v) : position(p), velocity(v) {}
};
