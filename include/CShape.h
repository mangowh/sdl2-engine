#pragma once

#include "Color.h"
#include "Physics.h"

#include <vector>

enum ShapeType { triangle, rect };

class CShape {
public:
  CShape(Physics::Vector2 v1, Physics::Vector2 v2, Physics::Vector2 v3,
         Color color = {255, 255, 255})
      : type(triangle), verts(std::vector({v1, v2, v3})), color(color) {}

  CShape(int width, int height, Color color = {255, 255, 255})
      : type(rect), width(width), height(height), color(color) {}

  const ShapeType type{triangle};

  int width{0};
  int height{0};

  std::vector<Physics::Vector2> verts;

  Color color{255, 255, 255};
};
