#include "pch.h"
#include "TestScene.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "ShowSetting.h"
#include "Object.h"
#include "Core.h"
#include "ResMgr.h"
#include "ShowSetting.h"

void TestScene::Init()
{
	ShowSetting::GetInst()->IsEscActive == false;
	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->Play(L"BGM");
}

void TestScene::Render(HDC _dc)
{
	Scene::Render(_dc);
	if (KEY_DOWN(KEY_TYPE::ESC))
	{
		ShowSetting::GetInst()->IsEscActive = true;
	}
}

void TestScene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
}
