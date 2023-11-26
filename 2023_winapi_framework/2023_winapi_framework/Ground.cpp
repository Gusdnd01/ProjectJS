#include "pch.h"
#include "Ground.h"
#include "Collider.h"
#include "Gravity.h"

Ground::Ground()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(3100.0f, 100.0f));
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

		float len = abs(objPos.y - pos.y);
		float value = (objScale.y / 2.0f + pos.y / 2.0f) - len;

		objPos = obj->GetPos();
		objPos.y -= (value - 0.1f);
		obj->SetPos(objPos);
	}
}
