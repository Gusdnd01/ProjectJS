#include "pch.h"
#include "Tile.h"
#include "CameraManager.h"
#include "Core.h"
#include "SelectGDI.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::BLACK;
	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, BRUSH_TYPE::BLACK);

	Vec2 renderPos = CameraManager::GetInst()->GetRenderPos(GetPos());

	RECT_RENDER(renderPos.x, renderPos.y, GetScale().x, GetScale().y, _dc);
}

