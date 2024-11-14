#pragma once

#include <string>

namespace Physics {

class Vector2 {
public:
  int x{0};
  int y{0};

  Vector2() {}

  Vector2(int _x, int _y) : x(_x), y(_y) {}

  Vector2 &operator=(const Vector2 &v);

  bool operator==(const Vector2 &v) const;
  bool operator!=(const Vector2 &v) const;

  Vector2 operator+(const int f) const;
  Vector2 operator+(const Vector2 &v) const;

  Vector2 operator-(const int f) const;
  Vector2 operator-(const Vector2 &v) const;

  Vector2 operator*(const int f) const;
  Vector2 operator*(const Vector2 &v) const;

  Vector2 operator/(const int f) const;
  // Vector2 operator/(const Vector2 &v) const;

  void operator+=(const Vector2 &v);

  void operator-=(const int f);
  void operator-=(const Vector2 &v);

  void operator*=(const int &f);
  void operator*=(const Vector2 &v);

  // void operator/=(const Vector2 &v);

  Vector2 clone() const;
  int magnitude() const;
  void normalize();
  Vector2 normalized() const;

  std::string toString() const;
};

struct Rect {
  Rect(Vector2 p1, Vector2 p2) : p1(p1), p2(p2), center((p1 + p2) / 2) {}

  int width() const { return p2.x - p1.x; }
  int height() const { return p2.y - p1.y; }

  const Vector2 p1;
  const Vector2 p2;
  const Vector2 center;

  void print() const;
};

bool checkCollision(const Rect &c1, const Rect &c2);
Vector2 getCollisionVect(const Rect &rect1, const Rect &rect2);

} // namespace Physics
