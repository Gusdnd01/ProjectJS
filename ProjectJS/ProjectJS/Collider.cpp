#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "Core.h"
Collider::Collider()
	: owner(nullptr)
{

}

Collider::~Collider()
{
}

void Collider::FinalUpdate()
{
	//object 위치를 따라가야한다.
	Vector2 vObjPos = owner->GetPos();
	finalPos = vObjPos + pos;
}

void Collider::Render(HDC _dc)
{
	HPEN newPen = GETINST(Core)->GetHPen(PEN_GROUP::GREEN);
	HPEN defaultPen = (HPEN)SelectObject(_dc, newPen);
	RECT_RENDER(pos.x, pos.y, scale.x, scale.y, _dc);
	SelectObject(_dc, defaultPen);
}
