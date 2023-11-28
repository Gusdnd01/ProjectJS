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
	arrowY = 0;
	moveY = 0;
	yIncrease = 100;
	bgmVolume = 1;
	effectVolume = 1;

	m_pTex = ResMgr::GetInst()->TexLoad(L"Setting", L"Texture\\GameP_Setting.bmp");	
}
void ShowSetting::Render(HDC _dc)
{
	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;


	if (IsActive)
	{
		TransparentBlt(_dc, x - 430, y - 250, 850, 500, m_pTex->GetDC(), 0, 0, 1920, 1080, RGB(255,255,255));
	
		if (moveY < yIncrease && KEY_DOWN(KEY_TYPE::DOWN))
		{
			moveY += yIncrease;
		}
		if (moveY > -yIncrease && KEY_DOWN(KEY_TYPE::UP))
		{
			moveY -= yIncrease;
		}

	
		arrowY = y + moveY;
		
		TextOut(_dc, x - 150, arrowY, L">", 1);
		TextOut(_dc, x + 150, arrowY, L"<", 1);

		if (arrowY == 460 && KEY_DOWN(KEY_TYPE::SPACE))
		{
			IsActive = false;
		}
	}
}

void ShowSetting::Update()
{
	if (IsActive)
	{
		if (arrowY == 260)
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
		else if (arrowY == 360)
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
		arrowY = 0;
		moveY = 0;
		yIncrease = 100;
	}
}
