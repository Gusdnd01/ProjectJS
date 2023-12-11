#include "pch.h"
#include "Intro_Scene.h"
#include "Object.h"
#include "Core.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "ShowSetting.h"
#include "ResMgr.h"
#include "Texture.h"

void Intro_Scene::Init()
{
	#pragma region reset

		moveY = 0;
		yIncrease = 50;
		arrowY = 0;

		TexSizeX = 150;
		TexSizeY = 27;

		start = 1;
		setting = 1;
		exiT = 1;
	#pragma endregion

	#pragma region TexLoad

		introTex = ResMgr::GetInst()->TexLoad(L"IntroBK", L"Texture\\Intro\\Game_Intro.bmp");
		GameStart = ResMgr::GetInst()->TexLoad(L"GameStartTex", L"Texture\\Intro\\GameStart.bmp");
		Setting = ResMgr::GetInst()->TexLoad(L"SettingTex", L"Texture\\Intro\\Setting.bmp");
		Exit = ResMgr::GetInst()->TexLoad(L"ExitTex", L"Texture\\Intro\\Exit.bmp");
	#pragma endregion

	ResMgr::GetInst()->LoadSound(L"IntroBGM", L"Sound\\IntroBGM.wav", true);
	ResMgr::GetInst()->Play(L"IntroBGM");
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, ShowSetting::GetInst()->GetBGM());
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, ShowSetting::GetInst()->GetSFX());
}

void Intro_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	int x = 10;//Core::GetInst()->GetResolution().x / 2 - 75 ;
	int y = Core::GetInst()->GetResolution().y / 2 + 150;

	TransparentBlt(_dc, 0, 0, 1280, 750, introTex->GetDC(), 0, 0, introTex->GetWidth(), introTex->GetHeight(), RGB(255, 0, 255));
	TransparentBlt(_dc, x + 40, y, TexSizeX * start, TexSizeY * start, GameStart->GetDC(), 0, 0, GameStart->GetWidth(), GameStart->GetHeight(), RGB(255, 0, 255));
	TransparentBlt(_dc, x, y + yIncrease, TexSizeX * setting, TexSizeY * setting, Setting->GetDC(), 0, 0, Setting->GetWidth(), Setting->GetHeight(), RGB(255, 0, 255));
	TransparentBlt(_dc, x, y + yIncrease * 2, TexSizeX * exiT, TexSizeY * exiT, Exit->GetDC(), 0, 0, Exit->GetWidth(), Exit->GetHeight(), RGB(255, 0, 255));

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

	switch (arrowY)
	{
	case 510: //게임 시작 버튼
	{
		start = 1.25f;
		setting = 1;
		exiT = 1;
	}
	break;
	case 560: //세팅 버튼
	{
		start = 1;
		setting = 1.25f;
		exiT = 1;
	}
	break;
	default: //게임 나가기 버튼
	{
		start = 1;
		setting = 1;
		exiT = 1.25f;
	}
	break;
	}
}

void Intro_Scene::Update()
{
	Scene::Update();

	if (ShowSetting::GetInst()->IsActive == false && KEY_DOWN(KEY_TYPE::SPACE))
	{
		switch (arrowY)
		{
		case 510: //게임 시작 버튼(360)
		{
			SceneMgr::GetInst()->LoadScene(L"IntroStoryScene");
		}
		break;
		case 560: //세팅 버튼(410)
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

void Intro_Scene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
}