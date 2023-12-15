#include "pch.h"
#include "PlayerItemUI.h"
#include "Animator.h"
#include "ResMgr.h"
#include "Player.h"

PlayerItemUI::PlayerItemUI()
	: m_bIsActive(false)
	, m_pTex(nullptr)
	, m_vOffsetPos {}
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"icon", L"Texture\\waterSkill.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnim(L"idle",m_pTex, Vec2(0.0f), Vec2(32.0f), Vec2(32.0f,0.0f),1, 0.1f);
	GetAnimator()->PlayAnim(L"idle", true);
}

PlayerItemUI::~PlayerItemUI()
{
}

void PlayerItemUI::Update()
{
	m_bIsActive = m_pPlayer->GetPlayerMode() == PLAYER_MODE::WATER;

	if (!m_bIsActive) return;
	
	Vec2 vOwnerPos = m_pOwner->GetPos();
	SetPos(vOwnerPos + m_vOffsetPos);
}

void PlayerItemUI::Render(HDC _dc) 
{
	if (!m_bIsActive) return;
	Component_Render(_dc);
}
