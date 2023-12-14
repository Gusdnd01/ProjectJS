#include "pch.h"
#include "Tree.h"
#include "Animator.h"
#include "Texture.h"
#include "ResMgr.h"

Tree::Tree()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"tree", L"Texture\\tree.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnim(L"idle", m_pTex, Vec2(0), Vec2(32), Vec2(32,0), 1, 0.1f);
	GetAnimator()->PlayAnim(L"idle", false);
}

Tree::~Tree()
{
}

void Tree::Render(HDC _dc)
{
	Component_Render(_dc);
}
