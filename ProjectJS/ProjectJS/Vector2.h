#pragma once
#include <assert.h>
class Vector2
{
public:
	Vector2();
	~Vector2();
	Vector2(float _x, float _y);
	Vector2(int _x, int _y);
	Vector2(POINT _pt);
	Vector2(const Vector2& _vec);

public:
	float Length() { return sqrt(pow(x, 2) + pow(y, 2)); }
	Vector2& Normalize() {
		float length = Length();
		assert(length != 0.f);
		x /= length;
		y /= length;
		return *this;
	}

public:
	float x;
	float y;
};

