#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

void Vector2::operator+=(const Vector2& v)
{
	add(v);
}

void Vector2::add(const Vector2& v)
{
	x += v.x;
	y += v.y;
}