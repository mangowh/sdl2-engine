#include "Physics.h"

Physics::Vector2 &Physics::Vector2::operator=(const Physics::Vector2 &v) {
  x = v.x;
  y = v.x;

  return *this;
}

bool Physics::Vector2::operator==(const Physics::Vector2 &v) const {
  return x == v.x && y == v.y;
}

bool Physics::Vector2::operator!=(const Physics::Vector2 &v) const {
  return x != v.x || y != v.y;
}

Physics::Vector2 Physics::Vector2::operator+(const int f) const {
  return Physics::Vector2(x + f, y + f);
}

Physics::Vector2 Physics::Vector2::operator+(const Physics::Vector2 &v) const {
  return Physics::Vector2(x + v.x, y + v.y);
}

Physics::Vector2 Physics::Vector2::operator-(const int f) const {
  return Physics::Vector2(x - f, y - f);
}

Physics::Vector2 Physics::Vector2::operator-(const Physics::Vector2 &v) const {
  return Physics::Vector2(x - v.x, y - v.y);
}

Physics::Vector2 Physics::Vector2::operator*(const int f) const {
  return Physics::Vector2(x * f, y * f);
}

Physics::Vector2 Physics::Vector2::operator*(const Physics::Vector2 &v) const {
  return Physics::Vector2(x * v.x, y * v.y);
}

Physics::Vector2 Physics::Vector2::operator/(const int f) const {
  return Physics::Vector2(x / f, y / f);
}

void Physics::Vector2::operator+=(const Physics::Vector2 &v) {
  x += v.x;
  y += v.y;
}

void Physics::Vector2::operator-=(const int f) {
  x -= f;
  y -= f;
}

void Physics::Vector2::operator-=(const Physics::Vector2 &v) {
  x -= v.x;
  y -= v.y;
}

void Physics::Vector2::operator*=(const int &f) {
  x *= f;
  y *= f;
}

void Physics::Vector2::operator*=(const Physics::Vector2 &v) {
  x *= v.x;
  y *= v.y;
}

Physics::Vector2 Physics::Vector2::clone() const {
  return Physics::Vector2(x, y);
}

int Physics::Vector2::magnitude() const {
  return static_cast<int>(std::sqrt(x * x + y * y));
}

void Physics::Vector2::normalize() {
  int mag = magnitude();
  if (mag > 0) {
    x /= mag;
    y /= mag;
  }
}

Physics::Vector2 Physics::Vector2::normalized() const {
  auto v = clone();
  v.normalize();
  return v;
}

bool Physics::checkCollision(const Rect &rect1, const Rect &rect2) {
  int r1x = rect1.p1.x;
  int r1y = rect1.p1.y;
  int r1w = rect1.width();
  int r1h = rect1.height();
  int r2x = rect2.p1.x;
  int r2y = rect2.p1.y;
  int r2w = rect2.width();
  int r2h = rect2.height();

  // are the sides of one rectangle touching the other?

  if (r1x + r1w >= r2x && // r1 right edge past r2 left
      r1x <= r2x + r2w && // r1 left edge past r2 right
      r1y + r1h >= r2y && // r1 top edge past r2 bottom
      r1y <= r2y + r2h) { // r1 bottom edge past r2 top
    return true;
  }
  return false;
}
