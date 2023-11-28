#include "pch.h"
#include "TestScene.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "ShowSetting.h"
#include "Object.h"
#include "Core.h"

void TestScene::Init()
{
	Object* pObj = new Object;
	pObj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, OBJECT_GROUP::DEFAULT);

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
