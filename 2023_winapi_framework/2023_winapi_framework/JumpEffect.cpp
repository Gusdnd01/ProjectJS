#include "pch.h"
#include "JumpEffect.h"
#include "ResMgr.h"
#include "Animator.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "EventMgr.h"

JumpEffect::JumpEffect()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Effect", L"Texture\\JumpEffect.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"JumpEffect", m_pTex, Vec2(0.0f, 0.0f), Vec2(32.0f, 32.0f), Vec2(32.0f, 0.f), 5, 0.05f);
	GetAnimator()->PlayAnim(L"JumpEffect", false);
}

JumpEffect::~JumpEffect()
{

}

void JumpEffect::Update()
{
	GetAnimator()->Update();
	per += fDT;

	if (per > 0.23f)
	{
		EventMgr::GetInst()->DeleteObject(this);
	}

}

void JumpEffect::Render(HDC _dc)
{
	Component_Render(_dc);
}
