#ifndef CSCHAPE_H
#define CSCHAPE_H

#include "Color.h"
#include "Vector2.h"

#include <string>
#include <vector>

enum ShapeType { triangle, rect };

class CShape {
public:
  CShape(Vector2 v1, Vector2 v2, Vector2 v3, Color color = {255, 255, 255})
      : type(triangle), verts(std::vector({v1, v2, v3})), color(color) {}

  CShape(float width, float height, Color color = {255, 255, 255})
      : type(rect), width(width), height(height), color(color) {}

  const ShapeType type{triangle};

  float width{0};
  float height{0};

  std::vector<Vector2> verts;

  Color color{255, 255, 255};
};

#endif // CSCHAPE_H