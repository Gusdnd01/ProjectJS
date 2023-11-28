#include "pch.h"
#include "Ground.h"
#include "Collider.h"
#include "Gravity.h"

Ground::Ground()
{
	CreateCollider();
}

Ground::~Ground()
{
}

void Ground::Update()
{
}

void Ground::EnterCollision(Collider* _other)
{
	Object* obj = _other->GetObj();

	if (obj->GetName() == L"Player") {
		obj->GetGravity()->OnGround(true);

		Vec2 objPos = obj->GetPos();
		Vec2 objScale = obj->GetCollider()->GetScale();

		Vec2 pos = GetPos();
		Vec2 scale = GetCollider()->GetScale();
		float len = 0;
		len = objPos.y - pos.y;
		len = len <= 0 ? -len : len;
		float value = (objScale.y / 2.0f + scale.y / 2.0f) - len;

		objPos.y -= (value - 0.1f);
		obj->SetPos(objPos);
	}
}

void Ground::ExitCollision(Collider* _other)
{
	Object* obj = _other->GetObj();

	if (obj->GetName() == L"Player") {
		obj->GetGravity()->OnGround(false);
	}
}
