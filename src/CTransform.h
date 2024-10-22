#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "Vector2.h"

#include <vector>

class CTransform {
public:
  Vector2 pos{0, 0};
  Vector2 velocity{0, 0};
  Vector2 scale{0, 0};
  float angle = 0;

  CTransform() {};
  CTransform(const Vector2 &p) : pos(p) {}
  CTransform(const Vector2 &p, const Vector2 &v) : pos(p), velocity(v) {}
};

#endif // CTRANSFORM_H