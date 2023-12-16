#include "pch.h"
#include "GameEndVolume.h"
#include "Collider.h"
#include "SceneMgr.h"
#include "Texture.h"
#include "ResMgr.h"
#include "Animator.h"
GameEndVolume::GameEndVolume()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"sunLight", L"Texture\\Gate.bmp");
	CreateAnimator();
	
	GetAnimator()->CreateAnim(L"idle", m_pTex, Vec2(0), Vec2(16),Vec2(16.0f, 0.0f), 4, 0.1f);
	GetAnimator()->PlayAnim(L"idle", true);

	CreateCollider();

	GetCollider()->SetScale(Vec2(100.0f, 100.0f));
}

GameEndVolume::~GameEndVolume()
{
}

void GameEndVolume::Update() {
	GetAnimator()->Update();
}

void GameEndVolume::EnterCollision(Collider* other)
{
	SceneMgr::GetInst()->LoadScene(L"OutStoryScene");
}

void GameEndVolume::Render(HDC _dc)
{
	Component_Render(_dc);
}
