#include "pch.h"
#include "Collider.h"
#include "Core.h"

Collider::Collider()
	:owner(0),pos(0), bounds(0)
{
}

Collider::~Collider()
{
}

void Collider::LateUpdate()
{
}

//초록색으로 Gizmos그려주는 함수
void Collider::Gizmos(HDC _dc)
{
	HPEN newPen = GETINST(Core)->GetHPen(PEN_GROUP::GREEN);
	HPEN defaultPen = (HPEN)SelectObject(_dc, newPen);
	RECT_RENDER(pos.x, pos.y, bounds.x, bounds.y, _dc);
	SelectObject(_dc, defaultPen);
}

bool Collider::IsCollision()
{
	return false;
}
