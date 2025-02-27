#pragma once
#include"Vector2D.h"
class Transform
{
public:
	float X, Y;
	Vector2D Position;

	Transform(float x = 0, float y = 0) :X(x), Y(y) { Position = Vector2D(x, y); }
	Transform(Vector2D p) :Position(p) { X = p.X; Y = p.Y; }

	inline void TranslateX(float x) { X += x; }
	inline void TranslateY(float y) { Y += y; }
	inline void Translate(Vector2D v) { X += v.X; Y += v.Y; }
};

