#include "pch.h"
#include "ShowSetting.h"
#include "Core.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"

void ShowSetting::Init()
{
	arrowY = 0;
	moveY = 0;
	yIncrease = 100;
	bgmVolume = 1;
	effectVolume = 1;
}
void ShowSetting::Render(HDC _dc)
{
	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;

	if (IsActive)
	{
		Rectangle(_dc, x - 500, y - 250, x + 500, y + 250);
		
		TextOut(_dc, x, y - 220, L"GAME OPTIONS", 12);

		TextOut(_dc, x - yIncrease, y - yIncrease, L"BGM:", 4);
		TextOut(_dc, x - yIncrease, y, L"SFX:", 4);
		TextOut(_dc, x, y + yIncrease, L"BACK", 4);
	
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
