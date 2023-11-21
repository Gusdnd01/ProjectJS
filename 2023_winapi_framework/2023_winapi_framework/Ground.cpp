#include "pch.h"
#include "Ground.h"
#include "Collider.h"

Ground::Ground()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(3100.0f, 100.0f));
}

Ground::~Ground()
{
}
