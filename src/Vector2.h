#ifndef VECTOR2_H
#define VECTOR2_H

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

	bool operator== (const Vector2& v) const;
	bool operator!= (const Vector2& v) const;

	Vector2 operator+ (const Vector2& v) const;
	Vector2 operator- (const Vector2& v) const;

	Vector2 operator* (const float f) const;
	Vector2 operator* (const Vector2& v) const;

	Vector2 operator/ (const Vector2& v) const;

	void operator+= (const Vector2& v);
	void operator-= (const Vector2& v);
	void operator*= (const Vector2& v);
	void operator/= (const Vector2& v);

	void add(const Vector2& v);
	
	void normalize();
};

#endif // VECTOR2_H