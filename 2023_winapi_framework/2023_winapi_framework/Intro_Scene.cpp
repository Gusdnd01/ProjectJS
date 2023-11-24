#include "pch.h"
#include "Intro_Scene.h"
#include "Object.h"
#include "Core.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "ShowSetting.h"

int arrowY;

void Intro_Scene::Init()
{
}

void Intro_Scene::Render(HDC _dc)
{

	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;

	SetTextAlign(_dc, TA_CENTER);
	TextOut(_dc, x, y, L"START", 5);
	TextOut(_dc, x, y + yIncrease, L"SETTING", 7);
	TextOut(_dc, x, y + yIncrease * 2, L"EXIT", 4);


	if (moveY < 100 && KEY_DOWN(KEY_TYPE::DOWN))
	{
		moveY += yIncrease;
	}
	if (moveY > 0 && KEY_DOWN(KEY_TYPE::UP))
	{
		moveY -= yIncrease;
	}

	arrowY = y + moveY;

	TextOut(_dc, x - 50, arrowY, L">", 1);

	Scene::Render(_dc);
}

void Intro_Scene::Update()
{
	if (KEY_DOWN(KEY_TYPE::SPACE)) 
	{
		switch (arrowY)
		{
		case 360: //���� ���� ��ư
		{
			SceneMgr::GetInst()->LoadScene(L"Start_Scene");
		}
		break;
		case 410: //���� ��ư
		{
			ShowSetting::GetInst()->IsActive == true;
		}
		break;
		default: //���� ������ ��ư
		{
			exit(0);
		}
		break;
		}
	}
}