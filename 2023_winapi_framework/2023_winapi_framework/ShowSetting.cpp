#include "pch.h"
#include "ShowSetting.h"
#include "Core.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "Texture.h"
#include "Object.h"

void ShowSetting::Init()
{
	settingArrowY = 0;
	settingMoveY = -100;
	settingYIncrease = 100;

	escArrowY = 0;
	escMoveY = -100;
	escYIncrease = 65;

	bgmVolume = 10;
	effectVolume = 10;

	#pragma region Texture Load

	m_pTex_SettingPannel = ResMgr::GetInst()->TexLoad(L"Setting", L"Texture\\GameP_Setting.bmp");
	m_pTex_arrow = ResMgr::GetInst()->TexLoad(L"Arrow", L"Texture\\arrow.bmp");
	m_pTex_ESC = ResMgr::GetInst()->TexLoad(L"ESC", L"Texture\\GameP_ESC.bmp");
	m_pTex_SoundBar = ResMgr::GetInst()->TexLoad(L"SoundBar", L"Texture\\SoundBar.bmp");
	m_pTex_SoundBar_null = ResMgr::GetInst()->TexLoad(L"SoundBar_null", L"Texture\\SoundBar_null.bmp");
#pragma endregion
}
void ShowSetting::Render(HDC _dc)
{
	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;

	if (IsActive)
	{
		TransparentBlt(_dc, x - 430, y - 250, 850, 500, m_pTex_SettingPannel->GetDC(), 0, 0, 1920, 1080, RGB(255,0,255));
	
		if (settingMoveY < settingYIncrease && KEY_DOWN(KEY_TYPE::DOWN))
		{
			settingMoveY += settingYIncrease;
		}
		if (settingMoveY > -settingYIncrease && KEY_DOWN(KEY_TYPE::UP))
		{
			settingMoveY -= settingYIncrease;
		}

		#pragma region BGM SOUND

			for (int i = 0; i < 10; i++)
			{
				TransparentBlt(_dc, x + i * 13, y - 102, 10, 25, m_pTex_SoundBar_null->GetDC(), 0, 0, 200, 300, RGB(255, 255, 255));
			}
			for (int i = 0; i < bgmVolume; i++)
			{
				TransparentBlt(_dc, x + i * 13, y - 102, 10, 25, m_pTex_SoundBar->GetDC(), 0, 0, 200, 300, RGB(255, 255, 255));
			}

		#pragma endregion
		#pragma region SFX SOUND

			for (int i = 0; i < 10; i++)
			{
				TransparentBlt(_dc, x + i * 13, y - 5, 10, 25, m_pTex_SoundBar_null->GetDC(), 0, 0, 200, 300, RGB(255, 255, 255));
			}
			for (int i = 0; i < effectVolume; i++)
			{
				TransparentBlt(_dc, x + i * 13, y - 5, 10, 25, m_pTex_SoundBar->GetDC(), 0, 0, 200, 300, RGB(255, 255, 255));
			}

		#pragma endregion

		settingArrowY = y + settingMoveY;
		
		TransparentBlt(_dc, x - 170, settingArrowY, 20, 20, m_pTex_arrow->GetDC(), 0, 0, 300, 300, RGB(255,0,255));

		if (settingArrowY == 460 && KEY_DOWN(KEY_TYPE::SPACE))
		{
			IsActive = false;
		}
	}
	if (!IsActive && IsEscActive)
	{
		TransparentBlt(_dc, x - 430, y - 250, 850, 500, m_pTex_ESC->GetDC(), 0, 0, 1920, 1080, RGB(255, 0, 255));
		if (escMoveY < 80 && KEY_DOWN(KEY_TYPE::DOWN))
		{
			escMoveY += escYIncrease;
		}
		if (escMoveY > -100 && KEY_DOWN(KEY_TYPE::UP))
		{
			escMoveY -= escYIncrease;
		}
		
		escArrowY = y + escMoveY;

		TransparentBlt(_dc, x - 170, escArrowY, 20, 20, m_pTex_arrow->GetDC(), 0, 0, 300, 300, RGB(255, 0, 255));
	}
}

void ShowSetting::Update()
{
	if (IsActive)
	{
		if (settingArrowY == 260)
		{
			if (bgmVolume > 0 && KEY_DOWN(KEY_TYPE::LEFT))
			{
				bgmVolume -= 1;
			}
			if (bgmVolume < 10 && KEY_DOWN(KEY_TYPE::RIGHT))
			{
				bgmVolume += 1;
			}
			ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, bgmVolume * 0.1f);
		}
		else if (settingArrowY == 360)
		{
			if (effectVolume > 0 && KEY_DOWN(KEY_TYPE::LEFT))
			{
				effectVolume -= 1;
			}
			if (effectVolume < 10 && KEY_DOWN(KEY_TYPE::RIGHT))
			{
				effectVolume += 1;
			}
			ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, effectVolume * 0.1f);
		}
	}
	else
	{
		settingArrowY = 0;
		settingMoveY = -100;
		settingYIncrease = 100;
	}

	if (IsEscActive && KEY_DOWN(KEY_TYPE::SPACE))
	{
		if (escArrowY == 260) //계속하기
		{
			IsEscActive = false;
		}
		if (escArrowY == 325) //게임 다시하기
		{

		}
		if (escArrowY == 390) //게임 설정
		{
			IsActive = true;
		}
		if (escArrowY == 455) //게임 나가기
		{
			SceneMgr::GetInst()->LoadScene(L"Intro_Scene");
			IsEscActive = false;
		}
	}
	if (!IsEscActive)
	{
		escArrowY = 0;
		escMoveY = -100;
		escYIncrease = 65;
	}
}