#include "pch.h"
#include "HitEffect.h"
#include "ResMgr.h"
#include "Animator.h"
#include "TimeMgr.h"
#include "EventMgr.h"

HitEffect::HitEffect()
	: per(0)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"HitEffect", L"Texture\\HitEffect.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"HitEffect", m_pTex, Vec2(0.0f, 0.0f), Vec2(32.0f, 32.0f), Vec2(32.0f, 0.f), 5, 0.05f);
	GetAnimator()->PlayAnim(L"HitEffect", false);
}

HitEffect::~HitEffect()
{
}

void HitEffect::Update()
{
	GetAnimator()->Update();
	per += fDT;

	if (per > 0.23f)
	{
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void HitEffect::Render(HDC _dc)
{
	Component_Render(_dc);
}