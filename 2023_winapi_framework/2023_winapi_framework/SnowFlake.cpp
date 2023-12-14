#include "pch.h"
#include "SnowFlake.h"
#include "Animator.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "Texture.h"

SnowFlake::SnowFlake()
	: m_fTimer(0.0f)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"snow", L"Texture\\Snow.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnim(L"idle", m_pTex, Vec2(0), Vec2(80, 45),Vec2(80, 0),37, .1f);
	GetAnimator()->PlayAnim(L"idle",true);
}

SnowFlake::~SnowFlake()
{
}

void SnowFlake::Update()
{
	GetAnimator()->Update();
}

void SnowFlake::Render(HDC _dc)
{
	Component_Render(_dc);
}
