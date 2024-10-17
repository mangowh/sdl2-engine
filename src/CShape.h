#ifndef CSCHAPE_H
#define CSCHAPE_H

#include "Color.h"

#include <string>

enum ShapeType {
	circle,
	rect
};

class CShape
{
public:
	CShape(float radius, Color color = { 255,255,255 })
		: type(circle)
		, radius(radius)
		, color(color)
	{}

	CShape(float width, float height, Color color = { 255,255,255 })
		: type(rect)
		, width(width)
		, height(height)
		, color(color)
	{}

	const ShapeType type{ circle };

	// reserved for circle
	float radius{ 0 };

	// reserved for rect
	float width{ 0 };
	float height{ 0 };

	Color color{ 255,255,255 };
};

#endif // CSCHAPE_H