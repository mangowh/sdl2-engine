#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

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

  void operator*=(const Vector2 &v);

  void operator/=(const Vector2 &v);

  Vector2 clone() const;
  float magnitude() const;
  void normalize();
  Vector2 normalized() const;
};

#endif // VECTOR2_H
