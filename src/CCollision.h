#pragma once

#include "Vector2.h";

class CCollision
{
public:
	Vector2 center;
	float radius;

	CCollision(Vector2 center, float radius)
		: center(center)
		, radius(radius)
	{}
};