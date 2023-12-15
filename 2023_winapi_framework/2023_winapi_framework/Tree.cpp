#include "pch.h"
#include "Tree.h"
#include "Animator.h"
#include "Texture.h"
#include "ResMgr.h"
#include "CameraManager.h"
Tree::Tree()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"tree", L"Texture\\tree.bmp");
}

Tree::~Tree()
{
}

void Tree::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 renderPos = CameraManager::GetInst()->GetRenderPos(vPos);
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	TransparentBlt(_dc
		, (int)(renderPos.x - vScale.x / 2)
		, (int)(renderPos.y - vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));
}
