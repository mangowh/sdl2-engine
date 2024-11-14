#pragma once

#include "Physics.h"

enum class ColliderShape { circle, rect };

class CCollision {
public:
  ColliderShape shape;

  Physics::Vector2 center;

  // circle
  int radius;

  // aabb
  Physics::Vector2 p1;
  Physics::Vector2 p2;

  CCollision(Physics::Vector2 center, int radius)
      : shape(ColliderShape::circle), center(center), radius(radius) {}
  CCollision(Physics::Vector2 p1, Physics::Vector2 p2)
      : shape(ColliderShape::rect), p1(p1), p2(p2), center({(p1 + p2) / 2}) {}

  int w() const { return p2.x - p1.x; };
  int h() const { return p2.y - p1.y; };
};
