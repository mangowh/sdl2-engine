#ifndef PHYSICS_H
#define PHYSICS_H

class Vector2
{
public:
	float x = 0;
	float y = 0;

	Vector2() = default;

	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vector2 operator + (const Vector2& v) const;
	void operator += (const Vector2& v);

	void add(const Vector2& v);

};

class CTransform
{
public:
	Vector2 pos = { 0,0 };
	Vector2 velocity = { 0,0 };

	CTransform() {};

	CTransform(const Vector2& p, const Vector2& v) : pos(p), velocity(v) {}
};

class CShape
{

};

#endif