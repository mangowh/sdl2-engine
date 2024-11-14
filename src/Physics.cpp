#include "Physics.h"

#include <cmath>
#include <iostream>
#include <memory>

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

std::string Physics::Vector2::toString() const {
  return std::to_string(x) + ":" + std::to_string(y);
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

Physics::Vector2 Physics::getCollisionVect(const Rect &rect1,
                                           const Rect &rect2) {
  Vector2 collisionVec{};

  if (!checkCollision(rect1, rect2)) {
    return collisionVec;
  }

  std::cout << std::endl << "rect1" << std::endl;
  rect1.print();

  if (rect1.center.x < rect2.center.x) {
    collisionVec.x = 1;
  } else if (rect1.center.x < rect2.center.x) {
    collisionVec.x = -1;
  }

  if (rect1.center.y > rect2.center.y) {
    collisionVec.y = 1;
  } else if (rect1.center.y < rect2.center.y) {
    collisionVec.y = -1;
  }

  return collisionVec;
}

// TODO toString
void Physics::Rect::print() const {
  std::cout << "p1 =" << p1.x << ":" << p1.y << std::endl;
  std::cout << "p2 =" << p2.x << ":" << p2.y << std::endl;
  std::cout << "center =" << center.x << ":" << center.y << std::endl;
}
