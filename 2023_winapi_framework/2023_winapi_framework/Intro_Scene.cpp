#include "pch.h"
#include "Intro_Scene.h"
#include "Object.h"
#include "Core.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "ShowSetting.h"

void Intro_Scene::Init()
{
	moveY = 0;
	yIncrease = 50;
	arrowY = 0;
}

void Intro_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;

	SetTextAlign(_dc, TA_CENTER);
	TextOut(_dc, x, y, L"START", 5);
	TextOut(_dc, x, y + yIncrease, L"SETTING", 7);
	TextOut(_dc, x, y + yIncrease * 2, L"EXIT", 4);

	if (ShowSetting::GetInst()->IsActive == false)
	{
		if (moveY < 100 && KEY_DOWN(KEY_TYPE::DOWN))
		{
			moveY += yIncrease;
		}
		if (moveY > 0 && KEY_DOWN(KEY_TYPE::UP))
		{
			moveY -= yIncrease;
		}
	}

	arrowY = y + moveY;

	TextOut(_dc, x - 50, arrowY, L">", 1);
	TextOut(_dc, x + 50, arrowY, L"<", 1);

}

void Intro_Scene::Update()
{
	Scene::Update();

	if (ShowSetting::GetInst()->IsActive == false && KEY_DOWN(KEY_TYPE::SPACE))
	{
		switch (arrowY)
		{
		case 360: //게임 시작 버튼
		{
			SceneMgr::GetInst()->LoadScene(L"Start_Scene");
		}
		break;
		case 410: //세팅 버튼
		{
			ShowSetting::GetInst()->IsActive = true;
		}
		break;
		default: //게임 나가기 버튼
		{
			exit(0);
		}
		break;
		}
	}
}