#include "pch.h"
#include "Vector2.h"

Vector2::Vector2() :
	x(0.f), y(0.f)
{
}

Vector2::~Vector2()
{
}

Vector2::Vector2(float value)
	:x(value), y(value)
{
}

Vector2::Vector2(float _x, float _y)
	:x(_x), y(_y)
{
}

Vector2::Vector2(int _x, int _y):
	x((float)_x),y((float)_y)
{
}

Vector2::Vector2(POINT _pt):
	x((float)_pt.x), y((float)_pt.y)
{
}

Vector2::Vector2(const Vector2& _vec):
	x(_vec.x), y(_vec.y)
{
}
