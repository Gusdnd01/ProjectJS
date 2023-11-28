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
	settingMoveY = 0;
	settingYIncrease = 100;

	escArrowY = 0;
	escMoveY = -100;
	escYIncrease = 65;

	bgmVolume = 1;
	effectVolume = 1;

	m_pTex_SettingPannel = ResMgr::GetInst()->TexLoad(L"Setting", L"Texture\\GameP_Setting.bmp");
	m_pTex_arrow = ResMgr::GetInst()->TexLoad(L"Arrow", L"Texture\\arrow.bmp");
	m_pTex_ESC = ResMgr::GetInst()->TexLoad(L"ESC", L"Texture\\GameP_ESC.bmp");
}
void ShowSetting::Render(HDC _dc)
{
	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;


	if (IsActive)
	{
		TransparentBlt(_dc, x - 430, y - 250, 850, 500, m_pTex_SettingPannel->GetDC(), 0, 0, 1920, 1080, RGB(255,255,255));
	
		if (settingMoveY < settingYIncrease && KEY_DOWN(KEY_TYPE::DOWN))
		{
			settingMoveY += settingYIncrease;
		}
		if (settingMoveY > -settingYIncrease && KEY_DOWN(KEY_TYPE::UP))
		{
			settingMoveY -= settingYIncrease;
		}

	
		settingArrowY = y + settingMoveY;
		
		TransparentBlt(_dc, x - 170, settingArrowY, 20, 20, m_pTex_arrow->GetDC(), 0, 0, 300, 300, RGB(255,0,255));

		if (settingArrowY == 460 && KEY_DOWN(KEY_TYPE::SPACE))
		{
			IsActive = false;
		}
	}
	if (!IsActive && IsEscActive)
	{
		TransparentBlt(_dc, x - 430, y - 250, 850, 500, m_pTex_ESC->GetDC(), 0, 0, 1920, 1080, RGB(255, 255, 255));
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
				bgmVolume -= 0.1f;
			}
			if (bgmVolume < 1 && KEY_DOWN(KEY_TYPE::RIGHT))
			{
				bgmVolume += 0.1f;
			}
			ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, bgmVolume);
		}
		else if (settingArrowY == 360)
		{
			if (effectVolume > 0 && KEY_DOWN(KEY_TYPE::LEFT))
			{
				effectVolume -= 0.1f;
			}
			if (effectVolume < 1 && KEY_DOWN(KEY_TYPE::RIGHT))
			{
				effectVolume += 0.1f;
			}
			ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, effectVolume);
		}
	}
	else
	{
		settingArrowY = 0;
		settingMoveY = 0;
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
			exit(0);
		}
	}
	if (!IsEscActive)
	{
		escArrowY = 0;
		escMoveY = -100;
		escYIncrease = 65;
	}
}
