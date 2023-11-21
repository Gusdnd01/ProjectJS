#include "pch.h"
#include "IntroObj.h"
#include <tchar.h>
#include "TimeManager.h"
#include "KeyManager.h"

IntroObj::IntroObj()
{
}

IntroObj::~IntroObj()
{

}


void IntroObj::Render(HDC _dc)
{
	TextOut(_dc, arrowX, arrowY, L">", 1);
	TextOut(_dc, x, y, L"GAME START", 10);
	TextOut(_dc, x, y + 30, L"GAME SETTING", 12);
	TextOut(_dc, x, y + 60, L"EXIT", 4);
}

void IntroObj::Update()
{
	if (KEY_DOWN(KEY_TYPE::DOWN))
	{
		if (arrowY < y + 60)
		{
			arrowY += 30;
		}
	}

	if (KEY_DOWN(KEY_TYPE::UP))
	{
		if (arrowY > y)
		{

		arrowY -= 30;
		}
	}
	if (KEY_DOWN(KEY_TYPE::SPACE))
	{

	}

}