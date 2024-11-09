#pragma once

#include <cmath>
#include <memory>

namespace Physics {

class Vector2 {
public:
  float x = 0;
  float y = 0;

  Vector2() = default;

  Vector2(float _x, float _y) : x(_x), y(_y) {}

  Vector2 &operator=(const Vector2 &v);

  bool operator==(const Vector2 &v) const;
  bool operator!=(const Vector2 &v) const;

  Vector2 operator+(const float f) const;
  Vector2 operator+(const Vector2 &v) const;

  Vector2 operator-(const float f) const;
  Vector2 operator-(const Vector2 &v) const;

  Vector2 operator*(const float f) const;
  Vector2 operator*(const Vector2 &v) const;

  Vector2 operator/(const float f) const;
  Vector2 operator/(const Vector2 &v) const;

  void operator+=(const Vector2 &v);

  void operator-=(const float f);
  void operator-=(const Vector2 &v);

  void operator*=(const float &f);
  void operator*=(const Vector2 &v);

  void operator/=(const Vector2 &v);

  Vector2 clone() const;
  float magnitude() const;
  void normalize();
  Vector2 normalized() const;
};

struct Rect {
  Rect(Vector2 p1, Vector2 p2) : p1(p1), p2(p2) {};

  float width() const { return p2.x - p1.x; };
  float height() const { return p2.y - p1.y; };

  const Vector2 p1;
  const Vector2 p2;
};

bool checkCollision(const Rect &c1, const Rect &c2);
} // namespace Physics
