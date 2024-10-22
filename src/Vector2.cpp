#include "Vector2.h"

Vector2& Vector2::operator=(const Vector2& v)
{
	x = v.x;
	y = v.x;

	return *this;
}

bool Vector2::operator== (const Vector2& v) const
{
	return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const
{
	return x != v.x || y != v.y;
}

Vector2 Vector2::operator+(const float f) const
{
	return Vector2(x + f, y + f);
}

Vector2 Vector2::operator+ (const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const float f) const
{
	return Vector2(x - f, y - f);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float f) const
{
	return Vector2(x * f, y * f);
}

Vector2 Vector2::operator*(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator/(const float f) const
{
	return Vector2(x / f, y / f);
}

void Vector2::operator+= (const Vector2& v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator-=(const float f)
{
	x -= f;
	y -= f;
}

void Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

Vector2 Vector2::clone() const
{
	return Vector2(x, y);
}

float Vector2::magnitude() const
{
	return std::sqrt(x * x + y * y);
}

void Vector2::normalize() {
	float mag = magnitude();
	if (mag > 0.0f) {
		x /= mag;
		y /= mag;
	}
}

Vector2 Vector2::normalized() const
{
	auto v = clone();
	v.normalize();
	return v;
}
