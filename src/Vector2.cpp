#include "Vector2.h"

bool Vector2::operator== (const Vector2& v) const
{
	return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const
{
	return x != v.x || y != v.y;
}

Vector2 Vector2::operator+ (const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float f) const
{
	return Vector2(x * f, y * f);
}

void Vector2::operator+= (const Vector2& v)
{
	add(v);
}

void Vector2::add(const Vector2& v)
{
	x += v.x;
	y += v.y;
}