#include "pch.h"
#include "GameEndVolume.h"
#include "Collider.h"
#include "SceneMgr.h"

GameEndVolume::GameEndVolume()
{
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.0f, 100.0f));
}

GameEndVolume::~GameEndVolume()
{
}

void GameEndVolume::EnterCollision(Collider* other)
{
	SceneMgr::GetInst()->LoadScene(L"Intro_Scene");
}

void GameEndVolume::Render(HDC _dc)
{
	Object::Render(_dc);
}
