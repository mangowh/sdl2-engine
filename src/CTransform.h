#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "Vector2.h"

#include <vector>

class CTransform {
public:
  Vector2 pos{0.0, 0.0f};
  Vector2 prevPos{0.0f, 0.0f};
  Vector2 scale{1.0, 1.0};
  Vector2 velocity{0, 0};
  float angle = 0;

  CTransform() {};
  CTransform(const Vector2 &p) : pos(p) {}
  CTransform(const Vector2 &p, const Vector2 &v) : pos(p), velocity(v) {}
};

#endif // CTRANSFORM_H